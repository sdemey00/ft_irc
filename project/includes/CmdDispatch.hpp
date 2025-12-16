#pragma once
#include <string>
#include <map>
#include "Replies.hpp"
#include "Errors.hpp"
#include "Message.hpp"
#include "User.hpp"

class IRCCore;

// cmd list prototype
void cmdNick(IRCCore& core, User& user, const Message& msg);

class CommandDispatcher {
public:
    static void dispatch(IRCCore& core, User& user, const Message& msg);
};
