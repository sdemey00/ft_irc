/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:26 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/29 17:03:27 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

// KICK <channel> <nick> [:reason]

void cmdKick(IRCCore &core, User& user, const Message& msg) {
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
	if (!target || !channel->hasUser(target)) {
		user.send(ERR_NOSUCHNICK(targetName));
		return ;
	}
	channel->broadcast(RPL_KICK(user.getNick(), chanName, targetName, reason), NULL);
	channel->removeUser(target);
}
