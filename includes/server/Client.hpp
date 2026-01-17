/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:03:20 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:42:06 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <arpa/inet.h>		// sockaddr_in, socklen_t
#include <string>			// string
#include <poll.h>			// pollfd

#include "core/User.hpp"			// User
#include "Requestable.hpp"	// Requestable

class Client : public Requestable {
public:
	User			user;

	virtual void	handle_request(IRCCore* core);
	virtual void	handle_disconnect(IRCCore* core);
};
