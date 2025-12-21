/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:19:10 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/21 02:15:40 by mmichele         ###   ########.fr       */
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
	std::string			pass;
	bool				init;
	int					fd;
	pollfd				server_poll;
	std::vector<pollfd>	polls;
	std::vector<Client>	clients;
	IRCCore				core;

	static void		_sighandler(int sig);

	void			_socket();
	void			_bind();
	void			_listen();
	void			_poll_init();
	void			_handle_events();
	void			_accept();
	
	Client*			fetch(const int& fd);
	void			erase();
	
	void			_send(Client& c, pollfd& mypoll);
	void			_recv(Client& c, pollfd& mypoll);


public:
	Server(char* raw_port, char* raw_pwd);
	~Server();
	void run();
};
