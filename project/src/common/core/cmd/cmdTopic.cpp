/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:45 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:39 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdTopic(IRCCore &core, User& user, const Message& msg) {
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
	if (msg.params.size() < 2) {
		std::string topic = channel->getTopic();
		if (topic.empty()) {
			return user.send(RPL_NOTOPIC(user.getNick(), chanName));
		}
		return user.send(RPL_TOPIC(user.getNick(), chanName, topic));
	}
	if (channel->isTopicRestrict() && !channel->isOperator(&user)) {
		return user.send(ERR_CHANOPRIVSNEEDED(chanName));
	}
	channel->setTopic(msg.params[1]);
	channel->broadcast(RPL_TOPICCHANGE(user.getPrefix(), chanName, msg.params[1]), NULL);
}
