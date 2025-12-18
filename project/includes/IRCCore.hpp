/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:14 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:15 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <sstream>

#include "User.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Replies.hpp"
#include "Errors.hpp"

class IRCCore;

typedef void (*CommandFn)(IRCCore&, User&, const Message&);

class IRCCore {
public:
	IRCCore(void);
	~IRCCore(void);
	
	// Users
	bool    nickExists(const std::string& nick) const;
	User*   getUserByNick(const std::string& nick);

	// Channels
	Channel*    getChannel(const std::string& name);
	Channel*    getOrCreateChannel(const std::string& name);

	// Protocol
	Message     parse(const std::string& line);
	void        dispatch(User& user, const Message& msg);

private:
	std::map<std::string, User*>        _users;
	std::map<std::string, Channel*>     _channels;
	std::map<std::string, CommandFn>    _cmds;
													// servername??
};

// Cmds
void	cmdNick(IRCCore &core, User& user, const Message& msg);
// void	cmdUser(User& user, const Message& msg);
// void	cmdJoin(User& user, const Message& msg);