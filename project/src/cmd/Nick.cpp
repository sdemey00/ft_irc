class IRCCore;
class User;
class Message;

#include "Nick.hpp"
#include "IRCCore.hpp"
#include "Replies.hpp"
#include "Errors.hpp"

void cmdNick(IRCCore& core, User& user, const Message& msg)
{
    if (msg.params.empty()) {
        user.send(ERR_NONICKNAMEGIVEN(user.getNick()));
        return;
    }
    std::string newNick = msg.params[0];
    if (core.nickExists(newNick)) {
        user.send(ERR_NICKNAMEINUSE(
            user.getNick().empty() ? "*" : user.getNick(),
            newNick,
            core.getServerName()
        ));
        return;
    }
    user.setNick(newNick);
    if (user.canRegister() && !user.isRegistered()) {
        user.setRegistered(true);
        user.send(RPL_WELCOME(user.getNick(), core.getServerName()));
    }
}



// :irc.example.com 433 currentNick foo :Nickname is already in use

// Errors.hpp
//
// inline std::string ERR_NICKNAMEINUSE(const std::string& currentNick,
//                                     const std::string& requestedNick,
//                                     const std::string& server)
// {
//     return ":" + server + " 433 " + currentNick + " " +
//            requestedNick + " :Nickname is already in use\r\n";
// }

