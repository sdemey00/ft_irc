#pragma once

class Channel {
	std::set<User*>	_members;
	std::set<User*>	_operators;

	public:
		std::string	name; // Channels names are strings (beginning with a '&' or '#' character) of length up to 200 characters.  Apart from the the requirement that the first character being either '&' or '#'; the only restriction on a channel name is that it may not contain any spaces (' '), a control G (^G or ASCII 7), or a comma (',' which is used as a list item separator by the protocol).

		Channel(void);
		~Channel(void);
		void	join(User *c);
		void	part(User *c);
		// void	broadcast(std::string &mes, User *dest = NULL);

		bool	isOperator(User *c) const;
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
//
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
//
//    The commands which may only be used by channel operators are:
//
//         KICK    - Eject a client from the channel
//         MODE    - Change the channel's mode
//         INVITE  - Invite a client to an invite-only channel (mode +i)
//         TOPIC   - Change the channel topic in a mode +t channel
//
//	   A channel operator is identified by the '@' symbol next to their
//	   nickname whenever it is associated with a channel (ie replies to the
//     NAMES, WHO and WHOIS commands).
