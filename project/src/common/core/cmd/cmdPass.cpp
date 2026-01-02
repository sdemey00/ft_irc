/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:42:43 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:28 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdPass(IRCCore &core, User& user, const Message& msg) {
    if (msg.params.empty()) {
        return user.send(ERR_NEEDMOREPARAMS(msg.command));
    }
    if (user.isRegistered()) {
        return user.send(ERR_ALREADYREGISTRED(user.getNick()));
    }
    if (msg.params[0] != core.getPassword()) {
        return user.send(ERR_PASSWDMISMATCH(user.getNick()));
    }
    user.setPasswordAccepted(true);
}
