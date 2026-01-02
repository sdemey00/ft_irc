/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:17:27 by mmichele          #+#    #+#             */
/*   Updated: 2026/01/01 12:40:36 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdQuit(IRCCore &core, User& user, const Message& msg) {
	(void)core;
	(void)user;
	(void)msg;
	std::string reason = "Client exited";
	if (msg.params.size() > 1) {
		reason = msg.params[1];
	}
	user.broadcast(RPL_QUIT(user.getPrefix(), reason));
}
