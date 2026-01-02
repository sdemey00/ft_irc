/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:44 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:25 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdPart(IRCCore&core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		return user.send(ERR_NOTREGISTERED(user.getNick()));
	}
	if (msg.params.empty()) {
		return user.send(ERR_NEEDMOREPARAMS(msg.command));
	}
	const std::string& chanName = msg.params[0];
	Channel* channel = core.getChannel(chanName);
	if (chanName[0] != '#' || !channel) {
		return user.send(ERR_NOSUCHCHANNEL(chanName));
	}
	if (!channel->hasUser(&user)) {
		return user.send(ERR_NOTONCHANNEL(chanName));
	}
	std::string reason = (msg.params.size() >= 2) ? msg.params[1] : "";
	channel->broadcast(RPL_PART(user.getPrefix(), chanName, reason), NULL);
	user.leaveChannel(channel);
	channel->removeUser(&user);
}
