/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:44 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:45 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

//	Command: PART
//    Parameters: <channel>{,<channel>}

void	cmdPart(IRCCore&core, User& user, const Message& msg) {
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
	channel->removeUser(&user);
	channel->broadcast(RPL_PART(user.getNick(), user.getUser(), user.getHost(), chanName), NULL);
}

//    The PART message causes the client sending the message to be removed
//    from the list of active users for all given channels listed in the
//    parameter string.

//    Numeric Replies:
//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_NOTONCHANNEL

//    Examples:
//    PART #twilight_zone             ; leave channel "#twilight_zone"
//    PART #oz-ops,&group5            ; leave both channels "&group5" and
//                                    "#oz-ops".
