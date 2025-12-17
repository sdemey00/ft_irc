/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:29 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:35:31 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <sstream>

Message Parser::parse(const std::string& line)
{
    Message				msg;
    std::istringstream	iss(line);
    std::string			token;

    if (!line.empty() && line[0] == ':') {
        iss >> token;
        msg.prefix = token.substr(1);
    }
    if (!(iss >> msg.command)) {
        return (msg);           // empty or invalid
    }
    while (iss >> token) {
        if (token[0] == ':') {
            std::string trailing = token.substr(1);
            std::string rest;
            std::getline(iss, rest);
            msg.params.push_back(trailing + rest);
            break;
        }
        msg.params.push_back(token);
    }
	msg.msgPrint();
    return (msg);
}
