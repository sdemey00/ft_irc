/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/14 14:33:17 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"	// Server

#include <sys/socket.h>	// socket, bind, listen, accept
#include <fcntl.h>		// fcntl
#include <cstring>		// memset
#include <cstdlib>		// isdigit
#include <unistd.h>		// close
#include <csignal>		// signal
#include <iostream>		// cout, endl
#include <poll.h>		// poll, pollfd

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
	init = 1;
	int optval = 1;
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) < 0)
		throw Errors::SetSockOpt();
	if (fcntl(server_sock, F_SETFL, O_NONBLOCK) < 0)
		throw Errors::Fcntl();
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

// Initialize poll events
void Server::_poll() {
	server_poll.fd = server_sock;
	server_poll.events = POLLIN;
	server_poll.revents = 0;
	polls.push_back(server_poll);
}

// Accept incoming connection
void Server::_accept() {
	verbose("Server::_accept()\n");
	Client c;
	c.client_sock = accept(server_sock, (sockaddr *)&c.sock_addr, &c.sock_len);
	if (c.client_sock < 0)
		throw Errors::Accept();
	if (fcntl(c.client_sock, F_SETFL, O_NONBLOCK))
		throw Errors::Fcntl();

	init = 1;
	clients.push_back(c);

	pollfd pfd;
	pfd.fd = c.client_sock;
	pfd.events = POLLIN;
	pfd.revents = 0;
	polls.push_back(pfd);
}

// Remove disconnected clients
void Server::erase() {
	for (std::vector<pollfd>::iterator it = polls.begin(); it != polls.end();) {
		if (it->fd == -1) { it = polls.erase(it); }
		else { it++; }
	}
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end();) {
		if (it->client_sock == -1) { it = clients.erase(it); }
		else { it++; }
	}
}

// Fetch client from poll event
Client* Server::fetch(const int& fd) {
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (clients[i].client_sock == fd)
			return &clients[i];
	}
	return 0;
}

Server::Server(char* raw_port, char* raw_pass) :
	port(std::atoi(raw_port)),
	pass(std::string(raw_pass)),
	init(0),
	server_sock(0),
	polls(0),
	clients(0)
{
	// Check for port input validity
	for (unsigned int i = 0; raw_port[i]; i++) {
		if (!std::isdigit(raw_port[i]))
			throw Errors::Port();
	}
	// Launch SIGINT handler
	signal(SIGINT, Server::_sighandler);
}

Server::~Server() {
	if (init)
		close(server_sock);
	for (unsigned int i = 0; i < polls.size(); i++) {
		close(polls[i].fd);
	}
}

void Server::run() {
	_socket();
	_bind();
	_listen();
	_poll();
	verbose("Handling events ...\n");
	while (run_state) {
		int polled = poll(polls.data(), polls.size(), -1);
		if (!polled) {
			std::cerr << "poll() = 0" << std::endl;
			continue ;
		}
		if (polled < 0)
			std::cerr << "poll() < 0" << std::endl;
		bool new_client = 0;
		for (size_t i = 0; i < polls.size(); ++i) {
			pollfd &curr_poll = polls[i];
			if (curr_poll.revents & POLLIN) {
				if (curr_poll.fd == server_sock) { new_client = 1; }
				else {
					Client* c = fetch(curr_poll.fd);
					if (c) { c->_recv(); }
				}
			}
			if (curr_poll.revents & POLLOUT) {
				Client* c = fetch(curr_poll.fd);
				if (c) { c->_send(); }
			}
			curr_poll.revents = 0;
		}
		if (new_client)
			_accept();
		erase();
	}
}
