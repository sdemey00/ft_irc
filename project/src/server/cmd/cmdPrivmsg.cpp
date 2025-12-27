/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 05:57:22 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/21 05:57:23 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

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
    const std::string& text = msg.params[1]; //trailing
    if (text.empty()) {
        user.send(ERR_NOTEXTTOSEND());
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
        const std::set<User*>& users = channel->getUsers();
        for (std::set<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
            if (*it != &user) {
                (*it)->send(RPL_PRIVMSG(user.getNick(), user.getUser(), user.getHost(), target, text));
            }
        }
		// OR channel->broadcast(privMsg); ->> queue a tous les users
    }
    else {
        User* targetUser = core.getUserByNick(target);
        if (!targetUser) {
            user.send(ERR_NOSUCHNICK(target));
            return ;
        }
    	//targetUser->send(":" + user.getNick() + " PRIVMSG " + target + " :" + text + CRLF);;
		targetUser->send(RPL_PRIVMSG(user.getNick(), user.getUser(), user.getHost(), target, text));  
		//user.send(":" + user.getNick() + " PRIVMSG " + target + " :" + text + CRLF);
    }
}

