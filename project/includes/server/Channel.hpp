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
	bool	isInviteOnly() const;
	bool	isTopicRestrict() const;
	bool	hasKeyPass() const;
	bool	getUserLimit() const;
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

// To create a new channel or become part of an existing channel, a user
//    is required to JOIN the channel.  If the channel doesn't exist prior
//    to joining, the channel is created and the creating user becomes a
//    channel operator.  If the channel already exists, whether or not your
//    request to JOIN that channel is honoured depends on the current modes
//    of the channel. For example, if the channel is invite-only, (+i),
//    then you may only join if invited.  As part of the protocol, a user
//    may be a part of several channels at once, but a limit of ten (10)
//    channels is recommended as being ample for both experienced and
//    novice users.

// Operators
// The channel operator (also referred to as a "chop" or "chanop") on a
//    given channel is considered to 'own' that channel.  In recognition of
//    this status, channel operators are endowed with certain powers which
//    enable them to keep control and some sort of sanity in their channel.
//    As an owner of a channel, a channel operator is not required to have
//    reasons for their actions, although if their actions are generally
//    antisocial or otherwise abusive, it might be reasonable to ask an IRC
//    operator to intervene, or for the usersjust leave and go elsewhere
//    and form their own channel.

//    The commands which may only be used by channel operators are:

//         KICK    - Eject a client from the channel
//         MODE    - Change the channel's mode
//         INVITE  - Invite a client to an invite-only channel (mode +i)
//         TOPIC   - Change the channel topic in a mode +t channel

// 	   A channel operator is identified by the '@' symbol next to their
// 	   nickname whenever it is associated with a channel (ie replies to the
//     NAMES, WHO and WHOIS commands).
