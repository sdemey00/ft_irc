/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:01 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

// Command: NICK
//    Parameters: <nickname> [ <hopcount> ]

void cmdNick(IRCCore &core, User& user, const Message& msg)
{
	if (msg.params.empty()) {
		user.send(ERR_NONICKNAMEGIVEN(user.getNick()));
		return ;
	}
	if (!user.getPasswordAccepted() && !core.getPassword().empty()) {
		return ;
	}
	std::string	newNick = msg.params[0];
	std::string	oldNick = user.getNick();
	if (core.nickExists(newNick) && newNick != oldNick) {
		if (oldNick.empty())
			oldNick = "*";
		user.send(ERR_NICKNAMEINUSE(oldNick, newNick));
		newNick = "*";
	}
	if (!oldNick.empty()) {
		core.removeUser(oldNick);
	}
	user.setNick(newNick);
	core.addUser(&user);
	if (user.isRegistered()) {
		user.send(RPL_NICK(oldNick, newNick));
	}
}


// NICK message is used to give user a nickname or change the previous
//    one.  The <hopcount> parameter is only used by servers to indicate
//    how far away a nick is from its home server.  A local connection has
//    a hopcount of 0.  If supplied by a client, it must be ignored.

//    If a NICK message arrives at a server which already knows about an
//    identical nickname for another client, a nickname collision occurs.
//    As a result of a nickname collision, all instances of the nickname
//    are removed from the server's database, and a KILL command is issued
//    to remove the nickname from all other server's database. If the NICK
//    message causing the collision was a nickname change, then the
//    original (old) nick must be removed as well.

//    If the server recieves an identical NICK from a client which is
//    directly connected, it may issue an ERR_NICKCOLLISION to the local
//    client, drop the NICK command, and not generate any kills.

//    Numeric Replies:
//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

//    Example:
//    NICK Wiz                        ; Introducing new nick "Wiz".
//    :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.
