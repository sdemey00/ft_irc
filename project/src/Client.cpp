/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/18 16:02:15 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>			// fcntl
#include <unistd.h>			// close
#include <iostream>			// cout, endl
#include <cstring>			// memcpy, isprint
#include <iomanip>			// setw
#include <poll.h>			// pollfd

#include "IRCCore.hpp"  	// core
#include "Errors.hpp"		// Errors
#include "Log.hpp"			// Log

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

void Client::_recv(pollfd& mypoll) {
	char buf[BUFFER_SIZE + 1];
	if (read_buffer.empty()) {  read_buffer = stash; }
	ssize_t n = recv(client_sock, buf, BUFFER_SIZE, 0);
	if (n > 0) {
		buf[n] = 0;
		Log::recv(0, client_sock, buf, n);
		read_buffer.append(buf, n);
		unsigned int crlf_idx = find_crlf(read_buffer.c_str(), read_buffer.length());
		if (crlf_idx > 0) {
			std::memcpy(stash, read_buffer.c_str() + crlf_idx + 1, n - find_crlf(buf, n));
			read_buffer = read_buffer.substr(0, crlf_idx - 1);
			Log::recv(1, client_sock, read_buffer.c_str(), read_buffer.length());
			// TODO Process message here
			IRCCore core;
			Message msg = IRCCore::parse(read_buffer);
			core.dispatch(user, msg);
			mypoll.events = POLLIN | POLLOUT;
			// END Process message
			crlf_idx = find_crlf(stash, std::strlen(stash));
			while (crlf_idx) {
				read_buffer = std::string(stash).substr(0, crlf_idx - 1);
				Log::recv(1, client_sock, read_buffer.c_str(), read_buffer.length());
				// TODO Process message here
				Message msg = IRCCore::parse(read_buffer);
				core.dispatch(user, msg);
				mypoll.events = POLLIN | POLLOUT;
				// END Process message
				std::memmove(stash, stash + crlf_idx + 1, std::strlen(stash + crlf_idx + 1) + 1);
				crlf_idx = find_crlf(stash, std::strlen(stash));
			}
			read_buffer.clear();
		}
	} else if (n == 0) {
		Log::disconnected(client_sock);
		close(mypoll.fd);
		mypoll.fd = -1;
		close(client_sock);
		client_sock = -1;
	}
}

void	Client::_send(pollfd& mypoll) {
	if (user._queue.empty()) { mypoll.events = POLLIN; return ; }
	ssize_t n = send(client_sock, user._queue.front().c_str(), user._queue.front().size(), 0);
	if (n < 0) { return ; }
	Log::send(client_sock, user._queue.front().substr(0, n - 2).c_str(), user._queue.front().substr(0, n - 2).length());
	if (static_cast<size_t>(n) == user._queue.front().size()) { user._queue.pop(); }
	else if (n > 0) { user._queue.front().erase(0, n); }
	if (!user._queue.size()) { mypoll.events = POLLIN; }
}
