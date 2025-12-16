/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/16 17:29:41 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>		// fcntl
#include <unistd.h>		// close
#include <iostream>		// cout, endl
#include <cstring>		// memcpy, isprint
#include <iomanip>		// setw

#include "Errors.hpp"	// Errors
#include "Server.hpp"	// log

static void log_buffer(const char buffer[BUFFER_SIZE], const unsigned int& length) {
	const unsigned int	width = 15;
	long int			left = length;

	while (left > 0) {
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				log << std::setw(3) << static_cast<int>(buffer[i + length - left]);
			}
			else { log << "   "; }
			log << " ";
		}
		log << ": \"";
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				if (std::isprint(buffer[i + length - left]))
					log << buffer[i + length - left];
				else
					log << "🯄";
			}
		}
		log << "\"" << std::endl;
		left -= width;
	}
}

static unsigned int find_crlf(const char buffer[BUFFER_SIZE], const unsigned int& length) {
	if (!length)
		return 0;
	for (unsigned int i = 0; i < length - 1; i++) {
		if (buffer[i] == '\r' && buffer[i + 1] == '\n')
			return i + 1;
	}
	return 0;
}

Client::Client() :
	read_buffer(""),
	write_buffer(""),
	sock_len(sizeof(sock_addr)),
	init(0)
{
	*stash = 0;
}

Client::~Client() {
	if (init)
		close(client_sock);
}

void Client::_recv() {
	char buf[BUFFER_SIZE];
	if (read_buffer.empty()) {  read_buffer = stash; }
	ssize_t n = recv(client_sock, buf, BUFFER_SIZE - 1, 0);
	if (n > 0) {
		buf[n] = 0;
		log << "PARTIAL  (" << std::setw(2) << client_sock << ") :\n";
		log_buffer(buf, n);
		read_buffer.append(buf, n);
		unsigned int crlf_idx = find_crlf(read_buffer.c_str(), read_buffer.length());
		if (crlf_idx > 0) {
			std::memcpy(stash, read_buffer.c_str() + crlf_idx + 1, n - find_crlf(buf, n));
			read_buffer = read_buffer.substr(0, crlf_idx - 1);
			log << "COMPLETE (" << std::setw(2) << client_sock << ") :\n";
			log_buffer(read_buffer.c_str(), read_buffer.length());
			std::cout << read_buffer << std::endl;
			// TODO Process message here
			// Message msg = Parser::parse(read_buffer);
			// CommandDispatcher::dispatch(core, client, msg);
			crlf_idx = find_crlf(stash, std::strlen(stash));
			while (crlf_idx) {
				read_buffer = std::string(stash).substr(0, crlf_idx - 1);
				log << "COMPLETE (" << std::setw(2) << client_sock << ") :\n";
				log_buffer(read_buffer.c_str(), read_buffer.length());
				std::cout << read_buffer << std::endl;
				// TODO Process message here
				std::memmove(stash, stash + crlf_idx + 1, std::strlen(stash + crlf_idx + 1) + 1);
				crlf_idx = find_crlf(stash, std::strlen(stash));
			}
			read_buffer.clear();
		}
	} else if (n == 0) {
		log << "Client " << client_sock << " disconnected.\n";
		std::cout << "Client " << client_sock << " disconnected.\n";
		close(client_sock);
		client_sock = -1;
	}
}

void	Client::_send() {
	if (write_buffer.empty())
		return ;
	ssize_t n = send(client_sock, write_buffer.data(), write_buffer.size(), 0);
	if (n > 0) { write_buffer.erase(0, n); }
}

// void Client::queue(const std::string& msg) {
//     write_buffer += msg;
// }