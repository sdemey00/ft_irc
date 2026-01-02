/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:46 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:41 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdUser(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.size() != 4) {
		return user.send(ERR_NEEDMOREPARAMS(msg.command));
	}
	if (user.isRegistered()) {
		return user.send(ERR_ALREADYREGISTRED(user.getNick()));
	}
	if (!user.getPasswordAccepted() && !core.getPassword().empty()) {
		return user.send(ERR_NOTREGISTERED(user.getNick()));
	}
	user.setUser(msg.params[0]);
	user.setHost(msg.params[1]); 
	user.setReal(msg.params.back());
	if (!user.getNick().empty() && user.getNick() != "*") {
		user.setRegistered(true);
		user.send(RPL_WELCOME(user.getNick()));
	}
}
