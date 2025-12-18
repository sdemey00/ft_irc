/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:17 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:18 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>

class Message {
	public:
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;
	void	msgPrint();
};

//	[:prefix] COMMAND param1 param2 :trailing
// <message> ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
// <prefix> ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
// <command> ::= <letter> { <letter> } | <number> <number> <number>
// <SPACE> ::= ' ' { ' ' }
// <params> ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
// <middle> ::= <Any *non-empty* sequence of octets not including SPACE
//  or NUL or CR or LF, the first of which may not be ':'>
// <trailing> ::= <Any, possibly *empty*, sequence of octets not including
//  NUL or CR or LF>
// <crlf> ::= CR LF
