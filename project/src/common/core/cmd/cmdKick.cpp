/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:26 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:44:17 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdKick(IRCCore &core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		user.send(ERR_NOTREGISTERED(user.getNick()));
		return ;
	}
	if (msg.params.size() < 2) {
		user.send(ERR_NEEDMOREPARAMS(msg.command));
		return ;
	}
	const std::string& chanName = msg.params[0];
    const std::string targetName = msg.params[1];
    std::string reason = (msg.params.size() >= 3) ? msg.params[2] : user.getNick();
    Channel* channel = core.getChannel(chanName);
	if (chanName[0] != '#' || !channel) {
		user.send(ERR_NOSUCHCHANNEL(chanName));
		return ;
	}
	if (!channel->hasUser(&user)) {
		user.send(ERR_NOTONCHANNEL(chanName));
		return ;
	}
	if (!channel->isOperator(&user)) {
        user.send(ERR_CHANOPRIVSNEEDED(chanName));
		return ;
	}
	User *target = core.getUserByNick(targetName);
	if (!target) {
		user.send(ERR_NOSUCHNICK(targetName));
		return ;
	}
	if (!channel->hasUser(target)) {
		user.send(ERR_USERNOTINCHANNEL(target->getNick(), chanName));
		return ;
	}
	channel->broadcast(RPL_KICK(user.getPrefix(), chanName, targetName, reason), NULL);
	target->leaveChannel(channel);
	channel->removeUser(target);
}
