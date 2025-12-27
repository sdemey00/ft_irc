/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:01 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/22 16:09:26 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>	// string

class Client {
	int				fd;
	bool			init;
	unsigned int	port;
	std::string		addr;
	std::string		pwd;

	std::string		name;

public:
	Client(char* address, char* raw_port, char* password, char* name);
	~Client();
	void	_socket();
	void	_connect();
	void	run();
};
