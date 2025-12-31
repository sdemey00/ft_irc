/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:14 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/19 19:18:52 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <sstream>

#include "core/User.hpp"
#include "core/Channel.hpp"
#include "core/Message.hpp"
#include "Replies.hpp"
#include "Errors.hpp"
#include "utils.hpp"

class IRCCore;

typedef void (*CommandFn)(IRCCore&, User&, const Message&);

class IRCCore {
public:
	IRCCore(const std::string pass);
	~IRCCore(void);
	
	// Users
	bool    nickExists(const std::string& nick) const;
	User*   getUserByNick(const std::string& nick);
	void    addUser(User* user);
	void    removeUser(const std::string& nick);

	// Channels
	Channel*    getChannel(const std::string& name);
	Channel*    getOrCreateChannel(const std::string& name);

	// Protocol
	static Message	parse(const std::string& line);
	void			dispatch(User& user, const Message& msg);
	std::string&	getPassword();

private:
	std::map<std::string, User*>        _users;
	std::map<std::string, Channel*>     _channels;
	std::map<std::string, CommandFn>    _cmds;
	std::string							_password;
	// servername??
};

// Cmds
void	cmdPass(IRCCore &core, User& user, const Message& msg);
void	cmdNick(IRCCore &core, User& user, const Message& msg);
void	cmdUser(IRCCore &core, User& user, const Message& msg);
void	cmdJoin(IRCCore &core, User& user, const Message& msg);
void	cmdPart(IRCCore&core, User& user, const Message& msg);
void	cmdPrivmsg(IRCCore &core, User& user, const Message& msg);
void	cmdQuit(IRCCore &core, User& user, const Message& msg);
void	cmdPing(IRCCore &core, User& user, const Message& msg);
void	cmdKick(IRCCore &core, User& user, const Message& msg);
void	cmdTopic(IRCCore &core, User& user, const Message& msg);
void	cmdInvite(IRCCore &core, User& user, const Message& msg);
void	cmdMode(IRCCore &core, User &user, const Message &msg);
