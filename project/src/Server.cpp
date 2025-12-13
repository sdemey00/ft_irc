/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 22:47:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"	// Server

#include <sys/socket.h>	// socket, bind, listen, accept
#include <fcntl.h>		// fcntl
#include <arpa/inet.h>	// sockaddr_in
#include <cstring>		// memset
#include <cstdlib>		// isdigit
#include <unistd.h>		// close
#include <csignal>		// signal
#include <iostream>		// cout, endl
#include <poll.h>		// poll

#include "Errors.hpp"	// Errors
#include "verbose.hpp"	// verbose

static bool run_state = 1;

void Server::_sighandler(int sig) {
	verbose("Server::_sighandler()\n");
	(void)sig;
	run_state = 0;
}

// Creating the socket
void Server::_socket() {
	verbose("Server::_socket()\n");
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
		throw Errors::Socket();
	is_server_sock = 1;
	int optval = 1;
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) < 0)
		throw Errors::SetSockOpt();
	//if (fcntl(server_sock, F_SETFL, O_NONBLOCK) < 0)
	//	throw Errors::Fcntl();
}

// Bind the socket to an address
void Server::_bind() {
	verbose("Server::_bind()\n");
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_sock, (sockaddr*)&addr, sizeof(addr)) < 0)
		throw Errors::Bind();
}

// Listening for connection
void Server::_listen() {
	verbose("Server::_listen()\n");
	if (listen(server_sock, SOMAXCONN) < 0)
		throw Errors::Listen();
}

// Check for events
void Server::_poll() {
	// TODO
}

// Accept incoming connection
void Server::_accept() {
	verbose("Server::_accept()\n");
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int new_client = accept(server_sock, (sockaddr*)&client_addr, &client_len);
	if (new_client < 0)
	   	throw Errors::Accept();
	//if (fcntl(new_client, F_SETFL, O_NONBLOCK) < 0)
	//	throw Errors::Fcntl();
	client_sock.push_back(new_client);
}

// Receiving data
void Server::_recv() {
	verbose("Server::_recv()\n");
	char buffer[1024];
	int bytes_read = recv(client_sock[0], buffer, sizeof(buffer) - 1, 0);
	if (bytes_read > 0) {
		buffer[bytes_read] = '\0';
		std::cout << "Received: " << buffer;
	}
}

// Send data
void Server::_send() {
	verbose("Server::_send()\n");
}

Server::Server(char* raw_port, char* raw_pass) :
	port(std::atoi(raw_port)),
	pass(std::string(raw_pass)),
	is_server_sock(0),
	server_sock(0),
	client_sock(0)
{
	// Check for port input validity
	for (unsigned int i = 0; raw_port[i]; i++) {
		if (!std::isdigit(raw_port[i]))
			throw Errors::Port();
	}
	// Launch SIGINT handler
	signal(SIGINT, Server::_sighandler);
	// Setup poll variables
}

Server::~Server() {
	if (is_server_sock)
		close(server_sock);
	for (unsigned int i = 0; i < client_sock.size(); i++) {
		close(client_sock[i]);
	}
}

void Server::run() {
	_socket();
	_bind();
	_listen();
	_accept();
	_recv();
	//while (run_state) {}
}
