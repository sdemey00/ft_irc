/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:20 by mmichele          #+#    #+#             */
/*   Updated: 2026/01/01 14:40:38 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bot/Client.hpp"

#include <unistd.h>			// close
#include <cstdlib>			// atoi, isdigit
#include <sys/socket.h>		// socket, connect
#include <arpa/inet.h>		// htons
#include <iostream>			// cerr, endl
#include <csignal>			// SIGINT
#include <sstream>			// stringstream
#include <cstring>			// memset, strlen
#include <fcntl.h>			// fcntl
#include <string>			// string

#include "Errors.hpp"		// Port, Socket
#include "sighandler.hpp"	// sighandler
#include "utils.hpp"		// isdigit
#include "RNG.hpp"			// roll, toss
#include "Log.hpp"			// logger

bool g_run_state = 1;

Client::Client(char* address, char* raw_port, char* password, char* name):
	init(0),
	port(std::atoi(raw_port)),
	addr(address),
	pwd(password),
	name(name)
{
	logger.open("bot.log");
	// Check for port input validity :
	if (!isdigit(raw_port, std::strlen(raw_port)))
		throw Errors::Port();
	// Launch SIGINT handler :
	signal(SIGINT, sighandler);
	// Initialize network :
	_socket();
	_connect();
	RNG::seed();
	pfd.events = POLLIN | POLLOUT;
	pfd.revents = 0;
	// Init commands :
	commands["!roll"] = roll;
	commands["!toss"] = toss;
}

Client::~Client() {
	if (init)
		close(pfd.fd);
}
	
void	Client::_socket() {
	pfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (pfd.fd < 0) { throw Errors::Socket(); }
	init = 1;
}

void	Client::_connect() {
	struct sockaddr_in serv_addr;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET , addr.c_str(), &serv_addr.sin_addr);
	if (connect(pfd.fd, (struct sockaddr*)&serv_addr , sizeof(serv_addr)) < 0)
		throw Errors::Connect();
	if (fcntl(pfd.fd, F_SETFL, O_NONBLOCK) < 0)
		throw Errors::Fcntl();
}

void	Client::_send(std::stringstream& raw_msg) {
	std::string	msg = raw_msg.str();
	long unsigned int n = 0;
	Log::send(pfd.fd, msg.substr(0, msg.length() - 2).c_str(), msg.substr(0, msg.length() - 2).length());
	do {
		n = send(pfd.fd, msg.c_str(), msg.length(), 0);
		msg.erase(0, n);
	} while(msg.length() > 0);
}

static std::string parse_dest(const Message& msg) {
	if (msg.params[0][0] == '#')
		return msg.params[0];
	return msg.prefix.substr(0, msg.prefix.find('!'));
}

void	Client::handle_request(IRCCore* core) {
	(void)core;
	Message	msg = IRCCore::parse(read_buffer);
	std::stringstream	reply;
	if (msg.command == "PRIVMSG" && msg.trailing[0] == '!')
	{
		std::map<std::string, void (*)(const std::string&, std::stringstream&)>::iterator command = commands.find(msg.trailing);
		std::string dest = parse_dest(msg);
		if (command == commands.end())
			unknown(dest, reply);
		else
			commands[msg.trailing](dest, reply);
	}
	else if (msg.command == "INVITE")
		reply << "JOIN " << msg.trailing << "\r\n";
	else { return ; }
	_send(reply);
}

void	Client::handle_disconnect(IRCCore* core) {
	(void)core;
	if (init)
		close(pfd.fd);
	init = 0;
	g_run_state = 0;
}

void	Client::run() {
	std::stringstream a; a << "PASS " << pwd << "\r\n"; _send(a);
	std::stringstream b; b << "NICK " << name << "\r\n"; _send(b);
	std::stringstream c; c << "USER " << name << " " << name << " " << addr << " :FT BOT\r\n"; _send(c);
	while (g_run_state) {
		int polled = poll(&pfd, 1, -1);
		if (polled == 0) { continue ; }
		else if (polled < 0) { break; }
		else { read(0); }
	}
}

