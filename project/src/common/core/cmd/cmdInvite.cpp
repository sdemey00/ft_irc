#include "core/IRCCore.hpp"

// Command: INVITE
//    Parameters: <nickname> <channel>

void	cmdInvite(IRCCore &core, User& user, const Message& msg) {
	if (msg.params.size() != 2) {
		user.send(ERR_NEEDMOREPARAMS(msg.command));
		return ;
	}
    const std::string& targetName = msg.params[0];
	const std::string& chanName = msg.params[1];
	Channel* channel = core.getChannel(chanName);
	if (chanName[0] != '#' || !channel) {
		user.send(ERR_NOSUCHCHANNEL(chanName));
		return ;
	}
	if (!channel->hasUser(&user)) {
		user.send(ERR_NOTONCHANNEL(chanName));
		return ;
	}
	if (!channel->isOperator(&user)) { //seulemt si channel->isInviteOnly()
		user.send(ERR_CHANOPRIVSNEEDED(chanName));
		return ;
	}
	User *target = core.getUserByNick(targetName);
	if (!target) {
		user.send(ERR_NOSUCHNICK(targetName));
		return ;
	}
	if (channel->hasUser(target)) {
		user.send(ERR_USERONCHANNEL(targetName, chanName));
		return ;
	}
	channel->addInvitation(target);
	user.send(RPL_INVITING(user.getNick(), targetName, chanName));
	target->send(RPL_INVITE(user.getNick(), targetName, chanName));
}
