/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:44 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdPart(IRCCore&core, User& user, const Message& msg) {
	if (!user.isRegistered()) {
		user.send(ERR_NOTREGISTERED(user.getNick()));
		return ;
	}
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
	channel->broadcast(RPL_PART(user.getNick(), user.getUser(), user.getHost(), chanName), NULL);
	channel->removeUser(&user);
}
