/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:01 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:54:45 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>			// string

#include "Requestable.hpp"	// Requestable

class Client : public Requestable {
	bool			init;
	unsigned int	port;
	std::string		addr;
	std::string		pwd;

	std::string		name;

	void	_socket();
	void	_connect();
	void	_send(std::string msg);

public:
	Client(char* address, char* raw_port, char* password, char* name);
	~Client();
	void	handle_request(IRCCore* core);
	void	handle_disconnect(IRCCore* core);
	void	run();
};
