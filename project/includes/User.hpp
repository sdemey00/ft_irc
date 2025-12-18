/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:23 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:24 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <set>
#include "Client.hpp"
#include "Channel.hpp"

class User {
public:
    User(void);
    User(std::string nick, std::string user, std::string realname);
	User(const User& other);
	User& operator=(const User& other);
    ~User(void);

    // Identity (RFC)
    const std::string& getNick() const;
    const std::string& getUser() const;
    const std::string& getRealName() const;

    void setNick(const std::string& nick);
    void setUser(const std::string& user);
    void setRealName(const std::string& realname);

    // Registration
    bool isRegistered() const;
    bool canRegister() const;
    void setRegistered(bool value);

    // Operator
    bool isOperator() const;
    void setOperator(bool value);

	// Method
	void send(const std::string &message);	
	std::string& getFrontQueue() const;

private:
    std::string         _nick;
    std::string         _user;
    std::string         _realname;
    bool		        _registered;
    bool		        _isOperator;
	std::queue<std::string>	_queue;
};

