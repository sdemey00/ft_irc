#include "IRCCore.hpp"

void	cmdPrivmsg(IRCCore &core, User& user, const Message& msg) {

    if (!user.isRegistered()) {
        user.send(ERR_NOTREGISTERED(user.getNick()));
        return ;
    }
    if (msg.params.size() < 2) {
        user.send(ERR_NEEDMOREPARAMS(msg.command));
        return ;
    }
    const std::string& target = msg.params[0];
    const std::string& text = msg.params[1];
    if (text.empty()) {
        user.send(ERR_NOTEXTTOSEND());
        return ;
    }
    if (target[0] == '#') {
        Channel* channel = core.getChannel(target);
        if (!channel) {
            user.send(ERR_NOSUCHCHANNEL(target));
            return ;
        }
        if (!channel->hasUser(&user)) {
            user.send(ERR_CANNOTSENDTOCHAN(target));
            return ;
        }
        const std::set<User*>& users = channel->getUsers();
        for (std::set<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
            if (*it != &user) {
                (*it)->send(RPL_PRIVMSG(user.getNick(), user.getUser(), user.getHost(), target, text));
            }
        }
    }
    else {
        User* targetUser = core.getUserByNick(target);
        if (!targetUser) {
            user.send(ERR_NOSUCHNICK(target));
            return ;
        }
		targetUser->send(RPL_PRIVMSG(user.getNick(), user.getUser(), user.getHost(), target, text));
    	user.send(":" + user.getNick() + " PRIVMSG " + target + " :" + text + CRLF);;
    }
}

