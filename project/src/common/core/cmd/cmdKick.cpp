/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:26 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:18 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdKick(IRCCore &core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		return user.send(ERR_NOTREGISTERED(user.getNick()));
	}
	if (msg.params.size() < 2) {
		return user.send(ERR_NEEDMOREPARAMS(msg.command));
	}
	const std::string& chanName = msg.params[0];
    const std::string targetName = msg.params[1];
    Channel* channel = core.getChannel(chanName);
	if (chanName[0] != '#' || !channel) {
		return user.send(ERR_NOSUCHCHANNEL(chanName));
	}
	if (!channel->hasUser(&user)) {
		return user.send(ERR_NOTONCHANNEL(chanName));
	}
	if (!channel->isOperator(&user)) {
		return user.send(ERR_CHANOPRIVSNEEDED(chanName));
	}
	User *target = core.getUserByNick(targetName);
	if (!target) {
		return user.send(ERR_NOSUCHNICK(user.getNick(), targetName));
	}
	if (!channel->hasUser(target)) {
		return user.send(ERR_USERNOTINCHANNEL(target->getNick(), chanName));
	}
    std::string reason = (msg.params.size() >= 3) ? msg.params[2] : user.getNick();
	channel->broadcast(RPL_KICK(user.getPrefix(), chanName, targetName, reason), NULL);
	target->leaveChannel(channel);
	channel->removeUser(target);
}
