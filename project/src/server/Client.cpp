/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:04:22 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 13:48:11 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Client.hpp"

#include <unistd.h>			// close
#include <poll.h>			// POLLIN

#include "Log.hpp"			// logger

void Client::handle_request(IRCCore* core) {
	Message msg = IRCCore::parse(read_buffer);
	core->dispatch(user, msg);
}

void Client::handle_disconnect(IRCCore* core) {
	Log::disconnected(pfd.fd, user.getNick());
	core->removeUser(user.getNick());
	if (pfd.fd >= 0)
		close(pfd.fd);
	pfd.fd = -1;
}
