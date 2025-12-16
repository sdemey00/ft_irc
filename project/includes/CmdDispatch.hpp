#pragma once
#include <string>
#include <map>
#include "Replies.hpp"
#include "Errors.hpp"
#include "Message.hpp"
#include "IRCCore.hpp"
#include "Channel.hpp"
#include "User.hpp"

// cmd list prototype
void cmdNick(IRCCore& core, User& user, const Message& msg);
void cmdJoin(IRCCore& core, User& user, const Message& msg);

class CommandDispatcher {
public:
    static void dispatch(IRCCore& core, User& user, const Message& msg);
};
