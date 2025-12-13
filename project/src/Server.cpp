/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 14:11:06 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Errors.hpp"

#include <cstdlib>		// isdigit
#include <cstring>      // memset
#include <unistd.h>     // close
#include <arpa/inet.h>  // sockaddr_in, inet_addr
#include <sys/socket.h> // socket, bind, listen, accept

Server::Server(): init(0) {}

Server::Server(char* raw_port, char* raw_pass): init(0) {
	for (unsigned int i = 0; raw_port[i]; i++) {
		if (!std::isdigit(raw_port[i]))
			throw Errors::PortError();
	}
	port = std::atoi(raw_port);
	pass = std::string(raw_pass);
	init = 1;
}

Server::Server(const Server& other): init(other.init), port(other.port), pass(other.pass) {}

void Server::operator=(const Server& other) {
	if (this != &other)
	{
		init = other.init;
		port = other.port;
		pass = other.pass;
	}
}

Server::~Server() {}

void Server::run() {
	if (!init)
		throw std::exception();
	// Creating the socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (sockfd < 0)
		throw Errors::SocketError();
	// Bind the socket to an address
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
		throw Errors::BindError();
		close(sockfd);
	}
	// Listening for connection
	if (listen(sockfd, 5) < 0) {
		throw Errors::ListenError();
		close(sockfd);
	}
	// Accept incoming connection
	sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	int clientSock = accept(sockfd, (sockaddr*)&clientAddr, &clientLen);
	if (clientSock < 0) {
	   	throw Errors::AcceptError();
	    close(sockfd);
	}
	// Receiving data
	char buffer[1024];
	int bytesRead = recv(clientSock, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead > 0) {
	    buffer[bytesRead] = '\0';
	    std::cout << "Received: " << buffer;
	}
	// Close connection
	close(clientSock);
	close(sockfd);
}
