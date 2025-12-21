#include "IRCCore.hpp"

void cmdPass(IRCCore &core, User& user, const Message& msg) {
    if (msg.params.empty()) {
        user.send(ERR_NEEDMOREPARAMS(msg.command));
        return ;
    }
    if (user.isRegistered()) {
        user.send(ERR_ALREADYREGISTRED(user.getNick()));
        return ;
    }
    if (msg.params[0] != core.getPassword()) {
        user.send(ERR_PASSWDMISMATCH(user.getNick()));
        return;
    }
    user.setPasswordAccepted(true);
}
