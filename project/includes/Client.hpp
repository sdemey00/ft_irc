/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:03:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/16 09:17:38 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>	// sockaddr_in, socklen_t
#include <string>		// string

#define BUFFER_SIZE 100

class Client {
	std::string		read_buffer;
	char			stash[BUFFER_SIZE];
	std::string		write_buffer;

	public:
	sockaddr_in		sock_addr;
	socklen_t		sock_len;
	bool			init;
	int				client_sock;

	// void queue(const std::string& msg);
	// User			user;
	
	Client();
	~Client();

	void	_recv();
	void	_send();
};
