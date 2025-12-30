/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requestable.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:46:37 by mmichele          #+#    #+#             */
/*   Updated: 2025/12/30 12:41:35 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>	// string
#include <poll.h>	// pollfd

#include "core/IRCCore.hpp"	// IRCCore

#define BUFFER_SIZE 60

class Requestable {
	char			stash[BUFFER_SIZE + 1];
	
protected:
	std::string		read_buffer;

	virtual void	handle_request(IRCCore* core) = 0;
	virtual void	handle_disconnect(IRCCore* core) = 0;

public:
	pollfd			pfd;
	void			read(IRCCore* core);

	Requestable();
	virtual ~Requestable();
};