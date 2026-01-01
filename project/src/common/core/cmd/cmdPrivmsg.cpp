/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 05:57:22 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdPrivmsg(IRCCore &core, User& user, const Message& msg) {
    if (!user.isRegistered()) {
        user.send(ERR_NOTREGISTERED(user.getNick()));
        return ;
    }
    if (msg.params.size() < 2) {
        user.send(ERR_NEEDMOREPARAMS(msg.command));
        return ;
    }
    const std::string& target = msg.params[0];
    const std::string& text = msg.params[1]; //trailing ?
    if (text.empty()) {
        user.send(ERR_NOTEXTTOSEND());
        return ;
    }
	if (target.empty()) {
    	user.send(ERR_NORECIPIENT(msg.command));
    	return ;
	}
    if (target[0] == '#') {
        Channel* channel = core.getChannel(target);
        if (!channel) {
            user.send(ERR_NOSUCHCHANNEL(target));
            return ;
        }
        if (!channel->hasUser(&user)) {
            user.send(ERR_CANNOTSENDTOCHAN(target));
            return ;
        }
		channel->broadcast(RPL_PRIVMSG(user.getPrefix(), target, text), &user);
    }
    else {
        User* targetUser = core.getUserByNick(target);
        if (!targetUser) {
            user.send(ERR_NOSUCHNICK(target));
            return ;
        }
		targetUser->send(RPL_PRIVMSG(user.getPrefix(), target, text));  
    }
}

