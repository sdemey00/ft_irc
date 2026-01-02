/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:34:26 by mmichele          #+#    #+#             */
/*   Updated: 2026/01/01 12:40:32 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

void cmdPing(IRCCore &core, User& user, const Message& msg)
{
	(void)core;
	(void)msg;
	user.send(":ft_irc PONG\r\n");
}
