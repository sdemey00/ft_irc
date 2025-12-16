/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:16 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:35:18 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User()
    : _registered(false), _isOperator(false){}

// Registration
bool	User::isRegistered() const {
    return (_registered);
}
bool	User::canRegister() const {
    return (!_nick.empty() && !_user.empty());
}
void	User::setRegistered(bool value) {
    _registered = value;
}

// Operator
bool	User::isOperator() const {
    return (_isOperator);
}
void	User::setOperator(bool value) {
    _isOperator = value;
}

// Setter / Getter
void	User::setNick(const std::string& nick) { _nick = nick; }
void	User::setUser(const std::string& user) { _user = user; }
void	User::setRealName(const std::string& realname) { _realname = realname; }
const std::string&	User::getNick() const { return (_nick); }
const std::string&	User::getUser() const { return (_user); }
const std::string&	User::getRealName() const { return (_realname); }

// Method
void	User::send(const std::string& message)
{
	(void)message;
    // if (!_client)
    //     return;
    //_client->send(message);
}
