/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:52:29 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/31 15:37:46 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bot/Client.hpp"

#include <sstream>			// stringstream

#include "RNG.hpp"			// roll, toss
#include "core/Message.hpp"	// Message

void	Client::roll(const std::string& dest, std::stringstream &reply) {
	reply << "PRIVMSG " << dest << " :" << RNG::roll() << "\r\n";
}

void	Client::toss(const std::string& dest, std::stringstream &reply) {
	reply << "PRIVMSG " << dest << " :";
	if (RNG::toss())
		reply << "heads";
	else
		reply << "tails";
	reply << "\r\n";
}

void	Client::unknown(const std::string& dest, std::stringstream &reply) {
	reply << "PRIVMSG " << dest << " :Unknown command\r\n";
}
