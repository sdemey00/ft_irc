/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:52:29 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 19:27:15 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

#include "RNG.hpp"	// roll, toss

void	Command::roll(Command &cmd) {
	cmd.reply << "PRIVMSG " << cmd.sender << " :🎲 " << RNG::roll() << " 🎲\r\n";
}

void	Command::toss(Command &cmd) {
	cmd.reply << "PRIVMSG " << cmd.sender << " :🪙 ";
	if (RNG::toss())
		cmd.reply << "heads";
	else
		cmd.reply << "tails";
	cmd.reply << " 🪙\r\n";
}

void	Command::unknown(Command &cmd) {
	cmd.reply << "PRIVMSG " << cmd.sender << " :Unknown command\r\n";
}
