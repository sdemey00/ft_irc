/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:03:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/21 02:55:04 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>	// sockaddr_in, socklen_t
#include <string>		// string

#include "User.hpp"

#define BUFFER_SIZE 120

class Client {
public:
	std::string		read_buffer;
	char			stash[BUFFER_SIZE + 1];
	sockaddr_in		sock_addr;
	socklen_t		sock_len;
	bool			init;
	int				fd;

	User			user;

	Client();
	~Client();
};
