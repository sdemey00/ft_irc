/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:40 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdJoin(IRCCore& core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		user.send(ERR_NOTREGISTERED(user.getNick()));
		return ;
	}
    if (msg.params.empty() || msg.params.size() > 2 ) {
        user.send(ERR_NEEDMOREPARAMS(msg.command));
        return ;
    }
    const std::string& chanName = msg.params[0];
	if (chanName[0] != '#') {
		user.send(ERR_NOSUCHCHANNEL(chanName));
		return ;
	}
	if (!isValidName(chanName.substr(1, chanName.length()))) {
		user.send(ERR_BADCHANMASK(user.getNick(), chanName));
		return ;
	}
    Channel* channel = core.getOrCreateChannel(chanName);
    if (channel->hasUser(&user)) {
        return ;
	}
	if (channel->isInviteOnly() && !channel->hasInvitation(&user)) {
		user.send(ERR_INVITEONLYCHAN(chanName));
		return ;
	}
	if (channel->hasKeyPass()) {
		if (msg.params.size() != 2) {
        	user.send(ERR_NEEDMOREPARAMS(msg.command));
			return ;
		}
		if (msg.params[1] != channel->getKeyPass()) {
			user.send(ERR_BADCHANNELKEY(chanName));
			return ;
		}
	}
	if (channel->getUserLimit() && channel->getUsers().size() >= channel->getUserLimit()) {
		user.send(ERR_CHANNELISFULL(chanName));
		return ;
	}
	if (channel->getUsers().empty()) {
    	channel->addOperator(&user);
	}
    channel->addUser(&user);
	user.joinChannel(channel);
    user.send(RPL_JOIN(user.getNick(), chanName));
    std::string names;
    const std::set<User*>& users = channel->getUsers();
    for (std::set<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
        if (!names.empty())
            names += " ";
        names += (*it)->getNick();
    }
	if (channel->getTopic().empty()) { user.send(RPL_NOTOPIC(chanName)); }
	else { user.send(RPL_TOPIC(user.getNick(), chanName, channel->getTopic())); }
    user.send(RPL_NAMREPLY(user.getNick(), "", chanName, names));
    user.send(RPL_ENDOFNAMES(user.getNick(), chanName));
}
