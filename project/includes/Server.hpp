/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:19:10 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/13 14:05:40 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>

class Server {
	bool			init;
	unsigned int	port;
	std::string		pass;

	public:
		Server();
		Server(char* raw_port, char* raw_pwd);
		Server(const Server& s);
		void operator=(const Server& s);
		~Server();
		void run();
};