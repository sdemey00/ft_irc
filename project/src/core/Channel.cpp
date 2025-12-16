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
#include "User.hpp"

Channel::Channel(const std::string& name)
    : _name(name) {}

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

// Topic
void	Channel::setTopic(const std::string& topic) { _topic = topic; }
const std::string&	Channel::getTopic() const { return (_topic); }

// first user to join become operator
