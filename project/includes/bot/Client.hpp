/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 04:26:01 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/31 14:59:03 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>			// string
#include <map>				// map
#include <sstream>			// stringstream

#include "Requestable.hpp"	// Requestable

class Client : public Requestable {
	bool			init;
	unsigned int	port;
	std::string		addr;
	std::string		pwd;

	std::string		name;

	void	_socket();
	void	_connect();
	void	_send(std::stringstream& raw_msg);

	std::map<std::string, void (*)(const std::string&, std::stringstream&)> commands;
	static void		roll(const std::string &dest, std::stringstream &reply);
	static void		toss(const std::string &dest, std::stringstream &reply);
	static void		unknown(const std::string &dest, std::stringstream &reply);

public:
	Client(char* address, char* raw_port, char* password, char* name);
	~Client();
	void	handle_request(IRCCore* core);
	void	handle_disconnect(IRCCore* core);
	void	run();
};
