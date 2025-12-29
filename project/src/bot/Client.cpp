/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/29 13:48:49 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

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

bool g_run_state = 1;

Client::Client(char* address, char* raw_port, char* password, char* name):
	init(0),
	port(std::atoi(raw_port)),
	addr(address),
	pwd(password),
	name(name) {
	// Check for port input validity :
	if (!isdigit(raw_port, std::strlen(raw_port)))
		throw Errors::Port();
	// Launch SIGINT handler :
	signal(SIGINT, sighandler);
	// Initialize network :
	_socket();
	_connect();
	RNG::seed();
}

Client::~Client() {
	if (init)
		close(fd);
}
	
void	Client::_socket() {
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) { throw Errors::Socket(); }
	init = 1;
}

void	Client::_connect() {
	struct sockaddr_in serv_addr;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET , addr.c_str(), &serv_addr.sin_addr);
	if (connect(fd, (struct sockaddr*)&serv_addr , sizeof(serv_addr)) < 0)
		throw Errors::Connect();
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw Errors::Fcntl();
}

void	Client::_send(std::string msg) {
	long unsigned int n = 0;
	do {
		n = send(fd, msg.c_str(), msg.length(), 0);
		msg.erase(0, n);
	} while(msg.length() > 0);
}

void	Client::_read() {
	
}

void	Client::run() {
	std::stringstream	msg;
	char				buf[100];

	std::memset(buf, 0, 100);
	msg << "PASS " << pwd << "\r\nNICK " << name << "\r\nUSER " << name << " " << name << " " << addr << " :FT BOT\r\n";
	_send(msg.str());
	msg.str("");
	while (g_run_state) {
		char c;
		if (read(fd, &c, 1) <= 0)
			continue ;
		std::cout << c;
	}
	//msg << "PRIVMSG " << "mmichele" << " :" << RNG::roll() << "\r\n";
	//_send(msg.str());
}

