/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 19:16:33 by mmichele         ###   ########.fr       */
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
#include "Command.hpp"		// Command

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

void	Client::_send(std::string msg) {
	long unsigned int n = 0;
	do {
		n = send(pfd.fd, msg.c_str(), msg.length(), 0);
		//Log::send(pfd.fd, msg.substr(0, n).c_str(), msg.substr(0, n).length());
		msg.erase(0, n);
	} while(msg.length() > 0);
}

void	Client::handle_server_requests() {
	// TODO
}

bool	Client::handle_commands() {
	Command		cmd(read_buffer);

	if (!cmd.isCmd)
		return 0;
	std::cout << cmd.command << " " << cmd.args << std::endl;
	if (cmd.type != cmd.NONE)
		cmd.commands[cmd.command](cmd);
	else 
		Command::unknown(cmd);
	_send(cmd.reply.str());
	return 1;
}

void	Client::handle_request(IRCCore* core) {
	(void)core;
	if (!handle_commands())
		handle_server_requests();
}

void	Client::handle_disconnect(IRCCore* core) {
	(void)core;
	if (init)
		close(pfd.fd);
	init = 0;
	g_run_state = 0;
}

void	Client::run() {
	std::stringstream	msg;
	msg << "PASS " << pwd << "\r\nNICK " << name << "\r\nUSER " << name << " " << name << " " << addr << " :FT BOT\r\n";
	_send(msg.str());
	while (g_run_state) {
		int polled = poll(&pfd, 1, -1);
		if (polled == 0) { continue ; }
		else if (polled < 0) { break; }
		else { read(0); }
	}
}

