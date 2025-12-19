/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:34:26 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/19 11:39:41 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"


void cmdPing(IRCCore &core, User& user, const Message& msg)
{
	(void)core;
	(void)msg;
	user.send(":ft_irc PONG\r\n");
}