/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:01 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:23 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdNick(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.empty()) {
		return user.send(ERR_NONICKNAMEGIVEN(user.getNick()));
	}
	if (!user.getPasswordAccepted() && !core.getPassword().empty()) {
		return ;
	}
	std::string	newNick = msg.params[0];
	std::string	oldNick = user.getNick();
	if (oldNick.empty())
		oldNick = "*";
	if (!isValidName(newNick)) {
		return user.send(ERR_ERRONEUSNICKNAME(oldNick, newNick));
	}
	if (core.nickExists(newNick) && newNick != oldNick) {
		user.send(ERR_NICKNAMEINUSE(oldNick, newNick));
		newNick = "*";
	}
	std::set<Channel*> tmp = user.getChannels();
	core.removeUser(oldNick);
	user.setNick(newNick);
	core.addUser(&user);
	if (!tmp.empty()) {
		for (std::set<Channel*>::const_iterator it = tmp.begin(); it != tmp.end(); it++) {
			(*it)->addUser(&user);
		}
	}
	if (!user.isRegistered() && !user.getUser().empty() && newNick != "*") {
		user.setRegistered(true);
		user.send(RPL_WELCOME(newNick));
	}
	if (user.isRegistered()) {
		user.broadcast(RPL_NICK(oldNick, newNick));
	}
}
