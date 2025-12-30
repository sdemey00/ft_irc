/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:17:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 19:27:21 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

#include <string>	// string
#include <sstream>	// stringstream

#include <iostream>

Command::Command(const std::string& cmd) : isCmd(0) {
	commands["!roll"] = Command::roll;
	commands["!toss"] = Command::toss;
	long unsigned int i = 1;
	while (cmd[i] != '!' && i < cmd.length() - 1) { sender += cmd[i]; i++;}
	if (i >= cmd.length() - 1) { return ; }
	while (cmd[i] != ':') { i++; }
	i++;
	while (i < cmd.length()) { command += cmd[i]; i++; }
	if (command[0] != '!')
		return ;
	isCmd = 1;
	while (i < cmd.length() && cmd[i] != ' ') { command += cmd[i]; i++; }
	args = cmd.substr(i);
	if (command == "!roll") { type = ROLL; }
	else if (command == "!toss") { type = TOSS; }
	else { type = NONE; }
}
