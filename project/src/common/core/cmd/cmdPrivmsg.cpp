/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 05:57:22 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:34 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdPrivmsg(IRCCore &core, User& user, const Message& msg) {
    if (!user.isRegistered()) {
        return user.send(ERR_NOTREGISTERED(user.getNick()));
    }
    if (msg.params.size() < 2) {
        return user.send(ERR_NEEDMOREPARAMS(msg.command));
    }
    const std::string& target = msg.params[0];
    const std::string& text = msg.params[1];
    if (text.empty()) {
        return user.send(ERR_NOTEXTTOSEND());
    }
	if (target.empty()) {
    	return user.send(ERR_NORECIPIENT(msg.command));
	}
    if (target[0] == '#') {
        Channel* channel = core.getChannel(target);
        if (!channel) {
            return user.send(ERR_NOSUCHCHANNEL(target));
        }
        if (!channel->hasUser(&user)) {
            return user.send(ERR_CANNOTSENDTOCHAN(target));
        }
		channel->broadcast(RPL_PRIVMSG(user.getPrefix(), target, text), &user);
    }
    else {
        User* targetUser = core.getUserByNick(target);
        if (!targetUser) {
            return user.send(ERR_NOSUCHNICK(user.getNick(), target));
        }
		targetUser->send(RPL_PRIVMSG(user.getPrefix(), target, text));  
    }
}

