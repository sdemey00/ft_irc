/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requestable.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:07:09 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Requestable.hpp"

#include <cstring>		// memcpy, strlen, memmove
#include <sys/socket.h>	// recv

#include "Log.hpp"		// Log
#include "core/IRCCore.hpp"	// IRCCore
#include "Errors.hpp"	// Recv

#include <stdio.h>		// perror
#include <errno.h>		// errno

Requestable::Requestable() :
	read_buffer("")
{
	stash[0] = 0;
	stash[BUFFER_SIZE] = 0;
	//pfd.fd = -1;
}

Requestable::~Requestable() {}

static unsigned int find_crlf(const char* str, const unsigned int& length) {
	if (!length)
		return 0;
	for (unsigned int i = 0; i < length - 1; i++) {
		if (str[i] == '\r' && str[i + 1] == '\n')
			return i + 1;
	}
	return 0;
}

void Requestable::read(IRCCore* core) {
	char buf[BUFFER_SIZE + 1];
	if (read_buffer.empty()) {  read_buffer = stash; }
	ssize_t n = recv(pfd.fd, buf, BUFFER_SIZE, 0);
	if (n > 0) {
		buf[n] = 0;
		Log::recv(0, pfd.fd, buf, n);
		read_buffer.append(buf, n);
		unsigned int crlf_idx = find_crlf(read_buffer.c_str(), read_buffer.length());
		if (crlf_idx > 0) {
			std::memcpy(stash, read_buffer.c_str() + crlf_idx + 1, n - find_crlf(buf, n));
			read_buffer = read_buffer.substr(0, crlf_idx - 1);
			Log::recv(1, pfd.fd, read_buffer.c_str(), read_buffer.length());
			handle_request(core);
			crlf_idx = find_crlf(stash, std::strlen(stash));
			while (crlf_idx) {
				read_buffer = std::string(stash).substr(0, crlf_idx - 1);
				Log::recv(1, pfd.fd, read_buffer.c_str(), read_buffer.length());
				handle_request(core);
				std::memmove(stash, stash + crlf_idx + 1, std::strlen(stash + crlf_idx + 1) + 1);
				crlf_idx = find_crlf(stash, std::strlen(stash));
			}
			read_buffer.clear();
		}
	} else if (n == 0) { handle_disconnect(core); }
	else { throw Errors::Recv(); }
}
