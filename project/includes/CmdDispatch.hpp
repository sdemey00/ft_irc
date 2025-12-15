#pragma once
#include <string>
#include <map>

class IRCCore;
class User;
class Message;

class CommandDispatcher {
public:
    static void dispatch(IRCCore& core, User& user, const Message& msg);
};