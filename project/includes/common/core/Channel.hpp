/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:08 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:09 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <set>

class User;

class Channel {
	public:
	Channel(void);
	Channel(const std::string& name);
	Channel(const Channel& other);
	Channel& operator=(const Channel& other);
	~Channel(void);

	// Membership
	void	addUser(User* user);
	void	removeUser(User* user);
	bool	hasUser(User* user) const;

	// Operators
	void	addOperator(User* user);
	void	removeOperator(User* user);
	bool	isOperator(User* user) const;

	void	addInvitation(User *user);
	void	removeInvitation(User* user);
	bool	hasInvitation(User* user) const;

	// Getter
	const std::string&		getName() const;
	const std::string&		getTopic() const;
	const std::set<User*>&	getUsers() const;
	const std::set<User*>&	getOps() const;
	// Setter
	void	setTopic(const std::string& topic);
	// Mode Getter
	bool				isInviteOnly() const;
	bool				isTopicRestrict() const;
	bool				hasKeyPass() const;
	unsigned int	getUserLimit() const;
	// Mode Setter
	void	setInviteOnly(bool value);
	void	setTopicRestrict(bool value);
	void	setKeyPass(std::string key);
	void	removeKeyPass();
	void	setUserLimit(unsigned int value);
	void	removeUserLimit();

	// Send to all users expect one (can be null)
	void	broadcast(const std::string& msg, User* except) const;

	private:
		std::string		_name;
		std::string		_topic;
		std::string		_key; // mode +k (password)
		unsigned int	_userLimit;
		std::set<User*>	_users;
		std::set<User*>	_operators;
		std::set<User*>	_invitations;
		// Mode
		bool			_i;	// set/remove invite-only
		bool			_t;	// set/remove restriction on TOPIC cmd
		bool			_k;	// set/remove channel key (password)
		bool			_l;	// set/remove the user limit to channel
};
