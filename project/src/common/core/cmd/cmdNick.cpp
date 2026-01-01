/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:01 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdNick(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.empty()) {
		user.send(ERR_NONICKNAMEGIVEN(user.getNick()));
		return ;
	}
	if (!user.getPasswordAccepted() && !core.getPassword().empty()) {
		return ;
	}
	std::string	newNick = msg.params[0];
	std::string	oldNick = user.getNick();
	if (oldNick.empty())
		oldNick = "*";
	if (!isValidName(newNick)) {
		user.send(ERR_ERRONEUSNICKNAME(oldNick, newNick));
		return ;
	}
	if (core.nickExists(newNick) && newNick != oldNick) {
		user.send(ERR_NICKNAMEINUSE(oldNick, newNick));
		newNick = "*";
	}
	if (!oldNick.empty()) {
		core.removeUser(oldNick);
	}
	user.setNick(newNick);
	core.addUser(&user);
	if (user.isRegistered()) {
		user.send(RPL_NICK(oldNick, newNick));	//broadcast a tous les channels???
	}
}
