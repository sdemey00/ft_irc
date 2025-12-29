/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:16 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/23 16:56:43 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() :
	_readyToSend(0),
	_registered(false),
	_isOperator(false),
	_passwordAccepted(false) {}

User::User(std::string nick, std::string user, std::string realname) :
	_readyToSend(0),
	_nick(nick),
	_user(user),
	_realname(realname),
	_registered(false),
	_isOperator(false),
	_passwordAccepted(false) {}

User::User(const User& other) {
	*this = other;
}

User& User::operator=(const User& other) {
	if (this != &other) {
		_nick = other._nick;
		_user = other._user;
		_realname = other._realname;
		_registered = other._registered;
		_isOperator = other._isOperator;
		_passwordAccepted = other._passwordAccepted;
		_readyToSend = other._readyToSend;
	}
	return (*this);
}

User::~User() {}

// Registration
bool	User::isRegistered() const { return (_registered); }
bool	User::canRegister() const { return (!_nick.empty() && !_user.empty()); }
// to get a user registered we need: PASS + NICK + USER
void	User::setRegistered(bool value) { _registered = value; }

// Operator
bool	User::isOperator() const { return (_isOperator); }
void	User::setOperator(bool value) { _isOperator = value; }

// Setters :
void	User::setNick(const std::string& nick) { _nick = nick; }
void	User::setHost(const std::string& host) { _hostname = host; };
void	User::setUser(const std::string& user) { _user = user; }
void	User::setReal(const std::string& realname) { _realname = realname; }
void	User::setPasswordAccepted(const bool value) { _passwordAccepted = value; }

// Getters :
const std::string&	User::getNick() const { return (_nick); }
const std::string&	User::getHost() const { return (_hostname); }
const std::string&	User::getUser() const { return (_user); }
const std::string&	User::getReal() const { return (_realname); }
bool				User::getPasswordAccepted() const { return (_passwordAccepted); }
std::string&		User::getFrontQueue() { return _queue.front(); };

// Send
void	User::send(const std::string& message)
{
	if (message.empty())
		return ;
	_readyToSend++;
	_queue.push(message);
}

