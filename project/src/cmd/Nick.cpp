/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:01 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:35:02 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class IRCCore;

#include "IRCCore.hpp"
#include "Replies.hpp"
#include "User.hpp"
#include "Message.hpp"

void cmdNick(IRCCore& core, User& user, const Message& msg)
{
    if (msg.params.empty()) {
        user.send(ERR_NONICKNAMEGIVEN(user.getNick())); //client.queue()
        return;
    }
    std::string newNick = msg.params[0];
    if (core.nickExists(newNick)) {
        user.send(ERR_NICKNAMEINUSE(newNick));
        return;
    }
    user.setNick(newNick);
    if (user.canRegister() && !user.isRegistered()) {
        user.setRegistered(true);
        user.send(RPL_WELCOME(user.getNick()));
    }
}

// void cmdNick(IRCCore& core, Client& client, const Message& msg)
// {
//     User& user = client.user;

//     if (msg.params.empty()) {
//         client.queue(ERR_NONICKNAMEGIVEN("*"));
//         return;
//     }
// }