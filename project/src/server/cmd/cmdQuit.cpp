/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:17:27 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/19 21:01:02 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

void cmdQuit(IRCCore &core, User& user, const Message& msg)
{
	(void)core;
	(void)user;
	(void)msg;
	//core.removeUser(user.getNick());
}