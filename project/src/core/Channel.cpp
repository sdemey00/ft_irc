/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:34:29 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:34:30 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : _name("") {}
Channel::Channel(const std::string& name) : _name(name) {}
Channel::Channel(const Channel& other) {
	*this = other;
}
Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		_name = other._name;
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

// Operators users
void	Channel::addOperator(User* user) {
	_operators.insert(user);
}
void	Channel::removeOperator(User* user) {
	_operators.erase(user);
}
bool	Channel::isOperator(User* user) const {
	return (_operators.find(user) != _operators.end());
}

// Getter / Setter
const std::string&		Channel::getTopic() const { return (_topic); }
const std::string&  	Channel::getName() const { return (_name); }
const std::set<User*>&	Channel::getUsers() const { return (_users); }
const std::set<User*>&	Channel::getOps() const { return (_operators); };
void	Channel::setTopic(const std::string& topic) { _topic = topic; }

// first user to join become operator
