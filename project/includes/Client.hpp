/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:03:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/18 09:30:36 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>	// sockaddr_in, socklen_t
#include <string>		// string
#include <poll.h>		// pollfd

#define BUFFER_SIZE 131

class Client {
	std::string		read_buffer;
	char			stash[BUFFER_SIZE];
	std::string		write_buffer;

public:
	sockaddr_in		sock_addr;
	socklen_t		sock_len;
	bool			init;
	int				client_sock;

	// User			user;
	
	Client();
	~Client();

	void	_recv(pollfd& mypoll);
	void	_send(pollfd& mypoll);
};
