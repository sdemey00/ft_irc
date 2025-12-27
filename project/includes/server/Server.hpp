/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:19:10 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/23 14:43:21 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>		// string
#include <vector>		// vector
#include <poll.h>		// pollfd
#include <fstream>		// ofstream

#include "Client.hpp"	// Client

class Server {
	unsigned int		port;
	pollfd				pfd;
	std::vector<pollfd>	polls;
	std::vector<Client>	clients;
	IRCCore				core;

	void		_socket();
	void		_bind();
	void		_listen();
	void		_handle_events();
	void		_accept();
	Client*		fetch(const int& fd);
	void		erase();
	void		_send(Client& c);
	void		_recv(Client& c);
	void		update_polls();

public:
	Server(char* raw_port, char* raw_pwd);
	~Server();
	void run();
};
