/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:17:35 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 19:27:26 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>	// string
#include <sstream>	// stringstream
#include <map>		// map

struct Command {
	enum Type {
		ROLL,
		TOSS,
		NONE
	};

	static void	roll(Command &cmd);
	static void	toss(Command &cmd);
	static void	unknown(Command &cmd);

	std::map<std::string, void (*)(Command&)> commands;

	Type		type;

	std::string	sender;
	std::string	command;
	std::string args;

	bool		isCmd;

	std::stringstream	reply;

	Command(const std::string& cmd);
};
