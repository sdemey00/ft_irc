/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:46 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void	cmdUser(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.size() != 4) {
		user.send(ERR_NEEDMOREPARAMS(msg.command));
		return ;
	}
	if (user.isRegistered()) {
		user.send(ERR_ALREADYREGISTRED(user.getNick()));
		return ;
	}
	if (!user.getPasswordAccepted() && !core.getPassword().empty()) {
		user.send(ERR_NOTREGISTERED(user.getNick()));
		return ;
	}
	user.setUser(msg.params[0]);
	user.setHost(msg.params[1]); 
	user.setReal(msg.params.back());
	if (!user.getNick().empty()) {
		user.setRegistered(true);
		user.send(RPL_WELCOME(user.getNick()));
	}
}
