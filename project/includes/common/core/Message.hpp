/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core/Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:17 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/23 14:37:56 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>		// vector
#include <iostream>		// ostream

class Message {
	public:
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;
	std::string					trailing;
};

std::ostream& operator<<(std::ostream& os, const Message& msg);

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
