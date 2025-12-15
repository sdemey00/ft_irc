/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:03:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/15 19:47:00 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>	// sockaddr_in, socklen_t
#include <string>		// string

#define BUFFER_SIZE 2	// Has to be greater than 1
#define MAX_CLIENTS 100

class Client {
	std::string		read_buffer;
	std::string		write_buffer;

	public:
	sockaddr_in		sock_addr;
	socklen_t		sock_len;
	bool			init;
	int				client_sock;
	
	Client();
	~Client();

	void	_recv();
	void	_send();
};
