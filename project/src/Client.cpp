/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/16 09:08:35 by mmichele         ###   ########.fr       */
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
	for (unsigned int i = 0; i < length; i++) {
		if (i < length - 1) { log << std::setw(3) << static_cast<int>(buffer[i]) << " "; }
		else { log << std::setw(3) << static_cast<int>(buffer[i]) << " : "; }
	}
	log << "\"";
	for (unsigned int i = 0; i < length; i++) {
		if (std::isprint(buffer[i]))
			log << buffer[i];
		else
			log << "🯄";
	}
	log << "\"\n";
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
	init(0) {}

Client::~Client() {
	if (init)
		close(client_sock);
}

// TODO return a vector<IrcRequests>
void Client::_recv() {
	static char		stash[MAX_CLIENTS][BUFFER_SIZE];
	char			buf[BUFFER_SIZE];
	if (read_buffer.empty()) {  read_buffer = stash[client_sock]; }
	ssize_t n = recv(client_sock, buf, BUFFER_SIZE - 1, 0);
	if (n > 0) {
		buf[n] = 0;
		log << "PARTIAL  (" << std::setw(2) << client_sock << ") : "; log_buffer(buf, n);
		read_buffer.append(buf, n);
		unsigned int crlf_idx = find_crlf(read_buffer.c_str(), read_buffer.length());
		if (crlf_idx > 0) {
			std::memcpy(stash[client_sock], read_buffer.c_str() + crlf_idx + 1, n - find_crlf(buf, n));
			read_buffer = read_buffer.substr(0, crlf_idx - 1);
			log << "COMPLETE (" << std::setw(2) << client_sock << ") : "; log_buffer(read_buffer.c_str(), read_buffer.length());
			std::cout << read_buffer << std::endl;
			// TODO Process message here
			crlf_idx = find_crlf(stash[client_sock], std::strlen(stash[client_sock]));
			while (crlf_idx) {
				read_buffer = std::string(stash[client_sock]).substr(0, crlf_idx - 1);
				log << "COMPLETE (" << std::setw(2) << client_sock << ") : "; log_buffer(read_buffer.c_str(), read_buffer.length());
				std::cout << read_buffer << std::endl;
				// TODO Process message here
				std::memmove(stash[client_sock], stash[client_sock] + crlf_idx + 1, std::strlen(stash[client_sock] + crlf_idx + 1) + 1);
				crlf_idx = find_crlf(stash[client_sock], std::strlen(stash[client_sock]));
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
