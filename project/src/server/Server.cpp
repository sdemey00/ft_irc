/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:16:23 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <sys/socket.h>		// socket, bind, listen, accept
#include <fcntl.h>			// fcntl
#include <cstring>			// memset
#include <cstdlib>			// atoi
#include <unistd.h>			// close
#include <csignal>			// signal, SIGINT
#include <iostream>			// cout, endl
#include <poll.h>			// poll, pollfd
#include <arpa/inet.h>		// htons

#include "Errors.hpp"		// Errors
#include "Log.hpp"			// Log
#include "sighandler.hpp"	// sighandler
#include "utils.hpp"		// isdigit

bool g_run_state = 1;

// Creating the socket
void Server::_socket() {
	logger << "Server::_socket()\n";

	pfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (pfd.fd < 0)
		throw Errors::Socket();
	int optval = 1;
	if (setsockopt(pfd.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) < 0)
		throw Errors::SetSockOpt();
	if (fcntl(pfd.fd, F_SETFL, O_NONBLOCK) < 0)
		throw Errors::Fcntl();
	pfd.events = POLLIN;
	pfd.revents = 0;
}

// Bind the socket to an address
void Server::_bind() {
	logger << "Server::_bind()\n";
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(pfd.fd, (sockaddr*)&addr, sizeof(addr)) < 0)
		throw Errors::Bind();
}

// Listening for connection
void Server::_listen() {
	logger << "Server::_listen()\n";
	if (listen(pfd.fd, SOMAXCONN) < 0)
		throw Errors::Listen();
}

// Accept incoming connection
void Server::_accept() {
	logger << "Server::_accept()\n";
	sockaddr_in		saddr;
	socklen_t		slen = sizeof(saddr);
	Client			c;

	c.pfd.fd = accept(pfd.fd, (sockaddr *)&saddr, &slen);
	if (c.pfd.fd < 0)
		throw Errors::Accept();
	if (fcntl(c.pfd.fd, F_SETFL, O_NONBLOCK) < 0)
		throw Errors::Fcntl();
	c.pfd.events = POLLIN;
	c.pfd.revents = 0;
	clients.push_back(c);
}

void Server::_handle_events() {
	bool new_client = 0;
	for (size_t i = 0; i < polls.size(); i++) {
		pollfd &curr_poll = polls[i];
		if (curr_poll.fd < 0) { continue ; }
		Client* c = fetch(curr_poll.fd);
		if (curr_poll.revents & POLLIN) {
			if (curr_poll.fd == pfd.fd) { new_client = 1; }
			else if (c) { _recv(*c); }
		}
		if (curr_poll.revents & POLLOUT) { if (c) { _send(*c); } }
		if (curr_poll.revents & POLLERR) {
			logger << curr_poll.fd << " has POLLERR" << std::endl;
		}
		if (curr_poll.revents & POLLHUP) {
			logger << curr_poll.fd << " has POLLHUP" << std::endl;
		}
		if (curr_poll.revents & POLLNVAL) {
			logger << curr_poll.fd << " has POLLNVAL" << std::endl;
		}
		curr_poll.revents = 0;
	}
	if (new_client)
		_accept();
	erase();
}

// Fetch client from poll event
Client* Server::fetch(const int& fd) {
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->pfd.fd == fd)
			return &(*it);
	}
	return 0;
}

// Remove disconnected clients
void Server::erase() {
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end();) {
		if (it->pfd.fd == -1) { it = clients.erase(it); }
		else { it++; }
	}
}

Server::Server(char* raw_port, char* raw_pass) :
	port(std::atoi(raw_port)),
	polls(0),
	clients(0),
	core(std::string(raw_pass))
{
	logger.open("server.log");
	// Check for port input validity :
	if (!isdigit(raw_port, std::strlen(raw_port)))
		throw Errors::Port();
	// Launch SIGINT handler :
	signal(SIGINT, sighandler);
	// Check that BUFFER_SIZE is in range :
	if (BUFFER_SIZE < 1)
		throw Errors::InvalidBufferSize();
	// Initialize network :
	_socket();
	_bind();
	_listen();
}

Server::~Server() {
	if (pfd.fd >= 0)
		close(pfd.fd);
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->pfd.fd >= 0)
			close(it->pfd.fd);
	}
}

void Server::update_polls() {
	polls.clear();
	polls.push_back(pfd);
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->user._readyToSend > 0)
			it->pfd.events = POLLIN | POLLOUT;
		else
			it->pfd.events = POLLIN;
		polls.push_back(it->pfd);
	}
}

void Server::run() {
	logger << "Server running ...\n";
	while (g_run_state) {
		update_polls();
		int polled = poll(polls.data(), polls.size(), -1);
		if (polled == 0) { continue ; }
		else if (polled < 0) { break ; }
		else { _handle_events(); }
	}
}

void Server::_recv(Client& c) { c.read(&core); }

void	Server::_send(Client& c) {
	ssize_t n = send(c.pfd.fd, c.user._queue.front().c_str(), c.user._queue.front().size(), 0);
	if (n < 0) { return ; }
	Log::send(c.pfd.fd, c.user._queue.front().substr(0, n - 2).c_str(), c.user._queue.front().substr(0, n - 2).length());
	if (static_cast<size_t>(n) == c.user._queue.front().size()) {
		c.user._queue.pop();
		c.user._readyToSend--;
	}
	else if (n > 0) { c.user._queue.front().erase(0, n); }
}
