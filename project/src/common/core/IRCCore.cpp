/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:13 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/31 15:36:47 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/IRCCore.hpp"

IRCCore::IRCCore(const std::string pass) : _password(pass) {
	_cmds["PASS"] = &cmdPass;
	_cmds["NICK"] = &cmdNick;
	_cmds["USER"] = &cmdUser;
	_cmds["JOIN"] = &cmdJoin;
	_cmds["PART"] = &cmdPart;
	_cmds["PRIVMSG"] = &cmdPrivmsg;
	_cmds["QUIT"] = &cmdQuit;
	_cmds["PING"] = &cmdPing;
	_cmds["KICK"] = &cmdKick;
	_cmds["INVITE"] = &cmdInvite;
	_cmds["TOPIC"] = &cmdTopic;
	_cmds["MODE"] = &cmdMode;
}

IRCCore::~IRCCore() {
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		delete it->second;
	}
	_channels.clear();
}

// Users
bool	IRCCore::nickExists(const std::string& nick) const {
	return (_users.find(nick) != _users.end());
}

void	IRCCore::addUser(User* user) {
	if (!user->getNick().empty())
		_users[user->getNick()] = user;
}

void	IRCCore::removeUser(const std::string& nick) {
	_users.erase(nick);
}

User*   IRCCore::getUserByNick(const std::string& nick) {
	if (!nickExists(nick))
		return (NULL);
	return (_users[nick]);
}

// Channels
Channel*    IRCCore::getChannel(const std::string& name) {
	if (_channels.count(name) == 0)
		return (NULL);
	return (_channels[name]);
}

Channel*    IRCCore::getOrCreateChannel(const std::string& name) {
	if (_channels.count(name) == 0)
		_channels[name] = new Channel(name);
	return (_channels[name]);
}

// Protocol
void IRCCore::dispatch(User& user, const Message& msg)
{
	std::string cmd = msg.command;
	if (cmd.empty() || cmd == "CAP")
		return ;
	for (size_t i = 0; i < cmd.size(); i++)
		cmd[i] = std::toupper(cmd[i]);
	std::map<std::string, CommandFn>::iterator it = _cmds.find(cmd);
	if (it == _cmds.end()) {
		user.send(ERR_UNKNOWNCOMMAND(user.getNick(), cmd));
		return ;
	}
	it->second(*this, user, msg);
}

Message IRCCore::parse(const std::string& line)
{
	Message				msg;
	std::istringstream	iss(line);
	std::string			token;

	if (!line.empty() && line[0] == ':') {
		iss >> token;
		msg.prefix = token.substr(1);
	}
	if (!(iss >> msg.command)) {
		return (msg);
	}
	while (iss >> token) {
		if (token[0] == ':') {
			std::string trailing = token.substr(1);
			std::string rest;
			std::getline(iss, rest);
			msg.params.push_back(trailing + rest);
			msg.trailing = trailing + rest;
			break ;
		}
		msg.params.push_back(token);
	}
	return (msg);
}

std::string& IRCCore::getPassword() { return (_password); }
