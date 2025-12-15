/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/15 11:47:54 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>		// fcntl
#include <unistd.h>		// close
#include <iostream>		// cout, endl

#include "Errors.hpp"	// Errors
#include "Verbose.hpp"	// Verbose

Client::Client() :
	sock_len(sizeof(sock_addr)),
	init(0) {}

Client::~Client() {
	if (init)
		close(client_sock);
}

void Client::_recv() {
	verbose << "Client::_recv()\n";
	char buf[2048];
	ssize_t n = recv(client_sock, buf, sizeof(buf), 0);
	if (n > 0) {
		read_buffer.append(buf, n);
		verbose << read_buffer;
	}
	else if (n == 0) {
		close(client_sock);
		client_sock = -1;
	}
}

void	Client::_send() {
	verbose << "Client::_send()\n";
	if (write_buffer.empty())
		return;
	ssize_t n = send(client_sock, write_buffer.data(), write_buffer.size(), 0);
	if (n > 0) { write_buffer.erase(0, n); }
}
