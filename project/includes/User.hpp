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
#include <queue>

#include "IRCCore.hpp"

class User {
public:
	User(void);
	User(std::string nick, std::string user, std::string realname);
	User(const User& other);
	User& operator=(const User& other);
	~User(void);

	// Identity (RFC)
	const std::string&	getNick() const;
	const std::string&	getHost() const;
	const std::string&	getUser() const;
	const std::string&	getReal() const;
	bool				getPasswordAccepted() const;

	void	setNick(const std::string& nick);
	void	setUser(const std::string& user);
	void	setHost(const std::string& host);
	void	setReal(const std::string& realname);
	void	setPasswordAccepted(bool value);

	// Registration
	bool	isRegistered() const;
	bool	canRegister() const;
	void	setRegistered(bool value);

	// Operator
	bool	isOperator() const;
	void	setOperator(bool value);

	// Send
	void			send(const std::string &message);	
	std::string&	getFrontQueue();

	std::queue<std::string>	_queue;

private:
	std::string	_nick;
	std::string	_user;
	std::string	_hostname;
	std::string	_realname;
	bool		_registered;
	bool		_isOperator;
	bool		_passwordAccepted;
};

