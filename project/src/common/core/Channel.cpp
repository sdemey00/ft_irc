/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:34:29 by sdemey            #+#    #+#             */
/*   Updated: 2026/01/01 12:40:58 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/Channel.hpp"
#include "core/User.hpp"

Channel::Channel(void) : _name(""), _key(""), _userLimit(0), _i(false), _t(false), _k(false), _l(false) {}
Channel::Channel(const std::string& name) : _name(name), _key(""), _userLimit(0), _i(false), _t(false), _k(false), _l(false) {}
Channel::Channel(const Channel& other) {
	*this = other;
}
Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		_name = other._name;
		_topic = other._topic;
		_key = other._key;
		_userLimit = other._userLimit;
		_i = other._i;
		_t = other._t;
		_k = other._k;
		_l = other._l;
	}
	return (*this);
}
Channel::~Channel() {}

// Membership
void	Channel::addUser(User* user) {
	_users.insert(user);
}
void	Channel::removeUser(User* user) {
	_users.erase(user);
	_operators.erase(user);
}
bool	Channel::hasUser(User* user) const {
	return (_users.find(user) != _users.end());
}

// Operators
void	Channel::addOperator(User* user) {
	_operators.insert(user);
}
void	Channel::removeOperator(User* user) {
	_operators.erase(user);
}
bool	Channel::isOperator(User* user) const {
	return (_operators.find(user) != _operators.end());
}

// Invitations
void	Channel::addInvitation(User *user) {
	_invitations.insert(user);
}
void	Channel::removeInvitation(User* user) {
	_invitations.erase(user);
}
bool	Channel::hasInvitation(User* user) const {
	return (_invitations.find(user) != _invitations.end());
}

// Getter :
const std::string&		Channel::getTopic() const { return (_topic); }
const std::string&  	Channel::getName() const { return (_name); }
const std::set<User*>&	Channel::getUsers() const { return (_users); }
const std::set<User*>&	Channel::getOps() const { return (_operators); };
// Setter :
void				Channel::setTopic(const std::string& topic) { _topic = topic; }
// Mode Getter :
bool				Channel::isInviteOnly() const { return (_i);}
bool				Channel::isTopicRestrict() const { return (_t);}
bool				Channel::hasKeyPass() const { return (_k);}
const std::string&	Channel::getKeyPass() const { return (_key);}
unsigned int		Channel::getUserLimit() const { return (_userLimit);}
// Mode Setter :
void				Channel::setInviteOnly(bool value) { _i = value;}
void				Channel::setTopicRestrict(bool value) { _t = value;}
void				Channel::setKeyPass(std::string key) { _key = key; _k = true; }
void				Channel::removeKeyPass() { _key = ""; _k = false; }
void				Channel::setUserLimit(unsigned int	value) { _userLimit = value;}
void				Channel::removeUserLimit() { _userLimit = 0; }

// Broadcast to all users in the channel except one (except can be null)
void	Channel::broadcast(const std::string& msg, User* except) const {
	for (std::set<User*>::const_iterator it = _users.begin(); it != _users.end(); ++it) {
		if (*it != except) {
			(*it)->send(msg);
		}
	}
}
