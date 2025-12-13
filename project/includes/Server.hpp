/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:19:10 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 17:29:09 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <vector>

#include <csignal>
#include <sys/types.h>

class Server {
	unsigned int		port;
	std::string			pass;
	int					server_sock;
	std::vector<int>	client_sock;

	static void _sighandler(int sig);

	void _socket();
	void _bind();
	void _listen();
	void _accept();
	void _recv();
	void _send();

	public:
		Server();
		Server(char* raw_port, char* raw_pwd);
		~Server();
		void run();
};