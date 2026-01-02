/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:40 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:14 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdJoin(IRCCore& core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		return user.send(ERR_NOTREGISTERED(user.getNick()));
	}
    if (msg.params.empty() || msg.params.size() > 2 ) {
        return user.send(ERR_NEEDMOREPARAMS(msg.command));
    }
    const std::string& chanName = msg.params[0];
	if (chanName.empty() || chanName[0] != '#') {
		return user.send(ERR_NOSUCHCHANNEL(chanName));
	}
	if (!isValidName(chanName.substr(1))) {
		return user.send(ERR_BADCHANMASK(user.getNick(), chanName));
	}
    Channel* channel = core.getChannel(chanName);
    if (channel) {
        if (channel->hasUser(&user))
            return ;
        if (channel->isInviteOnly() && !channel->hasInvitation(&user)) {
            return user.send(ERR_INVITEONLYCHAN(chanName));
        }
        if (channel->hasKeyPass()) {
            if (msg.params.size() < 2 || msg.params[1] != channel->getKeyPass()) {
                return user.send(ERR_BADCHANNELKEY(chanName));
            }
        }
        if (channel->getUserLimit() && channel->getUsers().size() >= channel->getUserLimit()) {
            return user.send(ERR_CHANNELISFULL(chanName));
        }
    }
    if (!channel)
        channel = core.getOrCreateChannel(chanName);
    if (channel->getUsers().empty())
        channel->addOperator(&user);
    channel->addUser(&user);
	user.joinChannel(channel);
    channel->removeInvitation(&user);
    channel->broadcast(RPL_JOIN(user.getPrefix(), chanName), NULL); //getPrefix()
	if (channel->getTopic().empty()) {
		user.send(RPL_NOTOPIC(chanName));
	}
	else {
		user.send(RPL_TOPIC(user.getNick(), chanName, channel->getTopic()));
	}
    std::string names;
    const std::set<User*>& users = channel->getUsers();
    for (std::set<User*>::const_iterator it = users.begin(); it != users.end(); it++) {
        if (!names.empty())
            names += " ";
		if (channel->isOperator(*it))
            names += "@";
        names += (*it)->getNick();
    }
    user.send(RPL_NAMREPLY(user.getNick(), "", chanName, names));
    user.send(RPL_ENDOFNAMES(user.getNick(), chanName));
}
