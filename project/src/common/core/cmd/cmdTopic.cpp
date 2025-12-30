/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:45 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:44:34 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

//   Command: TOPIC
//    Parameters: <channel> [<topic>]

void	cmdTopic(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.empty()) {
		user.send(ERR_NEEDMOREPARAMS(msg.command));
		return ;
	}
	const std::string& chanName = msg.params[0];
    Channel* channel = core.getChannel(chanName);
    if (chanName[0] != '#' || !channel) {
        user.send(ERR_NOSUCHCHANNEL(chanName));
        return ;
    }
	if (!channel->hasUser(&user)) {
		user.send(ERR_NOTONCHANNEL(chanName));
		return ;
	}
	if (msg.params.size() < 2) {
		std::string topic = channel->getTopic();
		if (topic.empty()) {
			user.send(RPL_NOTOPIC(chanName));
			return ;
		}
		user.send(RPL_TOPIC(user.getNick(), chanName, topic));
		return ;
	}
	if (!channel->isOperator(&user)) {
        user.send(ERR_CHANOPRIVSNEEDED(chanName));
		return ;
	}
	std::string newTopic = msg.params[1];
	channel->setTopic(newTopic);
	channel->broadcast(RPL_TOPICCHANGE(user.getNick(), user.getUser(), user.getHost(), chanName, newTopic), NULL);
}
