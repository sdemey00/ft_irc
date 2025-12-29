/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:42:43 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/29 09:42:45 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

void cmdPass(IRCCore &core, User& user, const Message& msg) {
    if (msg.params.empty()) {
        user.send(ERR_NEEDMOREPARAMS(msg.command));
        return ;
    }
    if (user.isRegistered()) {
        user.send(ERR_ALREADYREGISTRED(user.getNick()));
        return ;
    }
    if (msg.params[0] != core.getPassword()) {
        user.send(ERR_PASSWDMISMATCH(user.getNick()));
        return;
    }
    user.setPasswordAccepted(true);
}
