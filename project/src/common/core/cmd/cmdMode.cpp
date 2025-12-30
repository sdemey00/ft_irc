/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:03:30 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/30 12:44:24 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // atoi

#include "core/IRCCore.hpp"

// MODE #channel <modes> [params...]
// MODE #chan +i
// MODE #chan +k secret
// MODE #chan -k
// MODE #chan +o nick
// MODE #chan +l 10
// MODE #chan -l
// MODE #chan +it
// MODE #chan +o-o nick1 nick2

void	handleMode(IRCCore &core, User &user, const Message &msg, Channel *channel);
void	handleModeOperator(IRCCore &core, User &user, Channel *channel, const std::string &nick, bool adding);

void	cmdMode(IRCCore &core, User &user, const Message &msg)
{
    if (msg.params.size() < 2) { return ; }
    const std::string	&chanName = msg.params[0];
    Channel 			*channel = core.getChannel(chanName);
	if (chanName[0] != '#') { return; }
    if (!channel) {
        user.send(ERR_NOSUCHCHANNEL(chanName));
        return ;
    }
    if (!channel->hasUser(&user)) {
        user.send(ERR_NOTONCHANNEL(chanName));
        return ;
    }
    if (!channel->isOperator(&user)) {
        user.send(ERR_CHANOPRIVSNEEDED(chanName));
        return ;
    }
	handleMode(core, user, msg, channel);
}

void	handleMode(IRCCore &core, User &user, const Message &msg, Channel *channel)
{
	const std::string &modes = msg.params[1];
    size_t paramIndex = 2;
    bool adding = true;
	for (size_t i = 0; i < modes.size(); i++)
	{
		char m = modes[i];
		if (m == '+') {
			adding = true;
			continue ;
		}
		if (m == '-') {
			adding = false;
			continue ;
		}
		switch (m) {
			case 'i':
				channel->setInviteOnly(adding);
				break ;
			case 't':
				channel->setTopicRestrict(adding);
				break ;
			case 'k':
				if (adding) {
					if (paramIndex >= msg.params.size()) {
						user.send(ERR_NEEDMOREPARAMS(msg.command));
						return ; 
					}
					channel->setKeyPass(msg.params[paramIndex++]);
				} else { channel->removeKeyPass(); }
				break ;
			case 'o':
				if (paramIndex >= msg.params.size()) {
					user.send(ERR_NEEDMOREPARAMS(msg.command));
					return ;
				}
				handleModeOperator(core, user, channel, msg.params[paramIndex++], adding);
				break ;
			case 'l':
				if (adding) {
					if (paramIndex >= msg.params.size()) {
						user.send(ERR_NEEDMOREPARAMS(msg.command));
						return;
					}
					// check if < 0 /!/
					channel->setUserLimit(std::atoi(msg.params[paramIndex++].c_str()));
					std::cout << channel->getUserLimit() << std::endl;
				} else { channel->removeUserLimit(); }
				break ;
		}
	}
}

void	handleModeOperator(IRCCore &core, User &user, Channel *channel, const std::string &nick, bool adding)
{
    User *target = core.getUserByNick(nick);
    if (!target || !channel->hasUser(target)) {
        user.send(ERR_NOSUCHNICK(nick));
        return;
    }
    if (adding)
        channel->addOperator(target);
    else
        channel->removeOperator(target);
}


// TODO
// - better replies
// - handle mode without channel specifier, mode on user? What response ?
// - implement every mode check in corresponding cmd (join, topic, ..)
// - deep test