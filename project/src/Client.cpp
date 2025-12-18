/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/18 12:00:15 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>		// fcntl
#include <unistd.h>		// close
#include <iostream>		// cout, endl
#include <cstring>		// memcpy, isprint
#include <iomanip>		// setw
#include <poll.h>		// pollfd

#include "Errors.hpp"	// Errors
#include "Server.hpp"	// g_log

static void log_req(const char* str, const unsigned int& length) {
	const unsigned int	width = 12;
	long int			left = length;

	while (left > 0) {
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				g_log << std::setw(4) << static_cast<int>(str[i + length - left]);
			}
			else { g_log << "    "; }
			g_log << " ";
		}
		g_log << ": \"";
		for (unsigned int i = 0; i < width; i++) {
			if (i + length - left < length) {
				if (std::isprint(str[i + length - left]))
					g_log << str[i + length - left];
				else
					g_log << "⍰";
			}
		}
		g_log << "\"" << std::endl;
		left -= width;
	}
}

static unsigned int find_crlf(const char* str, const unsigned int& length) {
	if (!length)
		return 0;
	for (unsigned int i = 0; i < length - 1; i++) {
		if (str[i] == '\r' && str[i + 1] == '\n')
			return i + 1;
	}
	return 0;
}

Client::Client() :
	read_buffer(""),
	sock_len(sizeof(sock_addr)),
	init(0)
{
	*stash = 0;
}

Client::~Client() {
	if (init)
		close(client_sock);
}

void Client::handle_request(pollfd& mypoll, const std::string& str) {
	if (str == "CAP LS")  {
		callbacks.push(":ft_irc CAP * LS :\r\n");
		mypoll.events = POLLIN | POLLOUT;
	}
	else if (str == "CAP END") {
		callbacks.push(":ft_irc 001 user :Welcome to the Internet Relay Network user!user@127.0.0.1\r\n");
		callbacks.push(":ft_irc 002 user :Your host is server.name, running version ircd\r\n");
		callbacks.push(":ft_irc 003 user :This server was created today\r\n");
		callbacks.push(":ft_irc 004 user server.name ircd ov # \r\n");
		callbacks.push(":ft_irc 376 user :End of /MOTD command.\r\n");
		mypoll.events = POLLIN | POLLOUT;
	}
	else if (str == "PING ft_irc") {
		callbacks.push("PONG\r\n");
		mypoll.events = POLLIN | POLLOUT;
	}
}

void Client::_recv(pollfd& mypoll) {
	char buf[BUFFER_SIZE + 1];
	if (read_buffer.empty()) {  read_buffer = stash; }
	ssize_t n = recv(client_sock, buf, BUFFER_SIZE, 0);
	if (n > 0) {
		buf[n] = 0;
		g_log << "RECV partial  (" << std::setw(3) << client_sock << ") :\n";
		log_req(buf, n);
		read_buffer.append(buf, n);
		unsigned int crlf_idx = find_crlf(read_buffer.c_str(), read_buffer.length());
		if (crlf_idx > 0) {
			std::memcpy(stash, read_buffer.c_str() + crlf_idx + 1, n - find_crlf(buf, n));
			read_buffer = read_buffer.substr(0, crlf_idx - 1);
			g_log << "RECV complete (" << std::setw(3) << client_sock << ") :\n";
			log_req(read_buffer.c_str(), read_buffer.length());
			std::cout << read_buffer << std::endl;
			handle_request(mypoll, read_buffer);
			crlf_idx = find_crlf(stash, std::strlen(stash));
			while (crlf_idx) {
				read_buffer = std::string(stash).substr(0, crlf_idx - 1);
				g_log << "RECV complete (" << std::setw(3) << client_sock << ") :\n";
				log_req(read_buffer.c_str(), read_buffer.length());
				std::cout << read_buffer << std::endl;
				handle_request(mypoll, read_buffer);
				std::memmove(stash, stash + crlf_idx + 1, std::strlen(stash + crlf_idx + 1) + 1);
				crlf_idx = find_crlf(stash, std::strlen(stash));
			}
			read_buffer.clear();
		}
	} else if (n == 0) {
		g_log << "Client " << client_sock << " disconnected.\n";
		std::cout << "Client " << client_sock << " disconnected.\n";
		close(mypoll.fd);
		mypoll.fd = -1;
		close(client_sock);
		client_sock = -1;
	}
}

void	Client::_send(pollfd& mypoll) {
	if (callbacks.empty()) {
		std::cout << client_sock << " empty buffer" << std::endl;
		mypoll.events = POLLIN;
		return ;
	}
	ssize_t n = send(client_sock, callbacks.front().c_str(), callbacks.front().size(), 0);
	if (n < 0) { return ; }
	std::cout << "Server replied to " << client_sock << " with \"" << callbacks.front().substr(0, n - 2) << "\"" << std::endl;
	g_log << "SEND          (" << std::setw(3) << client_sock << ") : \n";
	log_req(callbacks.front().substr(0, n - 2).c_str(), std::strlen(callbacks.front().substr(0, n - 2).c_str()));
	if (static_cast<size_t>(n) == callbacks.front().size()) { callbacks.pop(); }
	else if (n > 0) { callbacks.front().erase(0, n); }
	if (!callbacks.size()) { mypoll.events = POLLIN; }
}
