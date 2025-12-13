/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:30 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 11:52:42 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <cstring>
#include <cstdlib>
#include <exception>
#include <algorithm>

Server::Server(): init(0) {}

Server::Server(char* raw_port, char* raw_pass): init(0) {
	for (unsigned int i = 0; raw_port[i]; i++) {
		if (!std::isdigit(raw_port[i]))
			throw std::exception();
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
}