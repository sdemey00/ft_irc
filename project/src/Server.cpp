/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 17:29:19 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Errors.hpp"

#include <cstdlib>		// isdigit
#include <cstring>      // memset
#include <unistd.h>     // close
#include <arpa/inet.h>  // sockaddr_in, inet_addr
#include <sys/socket.h> // socket, bind, listen, accept

static bool run_state = 1;

void Server::_sighandler(int sig) {
	(void)sig;
	run_state = 0;
}

// Creating the socket
void Server::_socket() {
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (server_sock < 0)
		throw Errors::SocketError();
}

// Bind the socket to an address
void Server::_bind() {
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_sock, (sockaddr*)&addr, sizeof(addr)) < 0)
		throw Errors::BindError();
}

// Listening for connection
void Server::_listen() {
	if (listen(server_sock, 5) < 0)
		throw Errors::ListenError();
}

void Server::_accept() {
	// Accept incoming connection
	sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	client_sock.push_back(accept(server_sock, (sockaddr*)&clientAddr, &clientLen));
	if (client_sock[0] < 0)
	   	throw Errors::AcceptError();
}

void Server::_recv() {
	// Receiving data
	char buffer[1024];
	int bytesRead = recv(client_sock[0], buffer, sizeof(buffer) - 1, 0);

	if (bytesRead > 0) {
	    buffer[bytesRead] = '\0';
	    std::cout << "Received: " << buffer;
	}
}

void Server::_send() {}

Server::Server() {}

Server::Server(char* raw_port, char* raw_pass) :
	port(std::atoi(raw_port)),
	pass(std::string(raw_pass)),
	server_sock(0),
	client_sock(0)
{
	// Check for port input validity
	for (unsigned int i = 0; raw_port[i]; i++) {
		if (!std::isdigit(raw_port[i]))
			throw Errors::PortError();
	}
	signal(SIGINT, Server::_sighandler);
}

Server::~Server() {
	close(server_sock);
	for (unsigned int i = 0; i < client_sock.size(); i++) {
		close(client_sock[i]);
	}
}

void Server::run() {
	_socket();
	_bind();
	while (run_state) {
		
	}
}
