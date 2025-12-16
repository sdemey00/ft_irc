#include "CommandDispatcher.hpp"
#include "Replies.hpp"
#include "Errors.hpp"
#include "Nick.hpp"
#include "UserCmd.hpp"
#include "Join.hpp"
#include "Privmsg.hpp"

typedef void (*CommandFn)(IRCCore&, User&, const Message&);

static std::map<std::string, CommandFn> g_commands = {
    {"NICK", &cmdNick},
    {"USER", &cmdUser},
    {"JOIN", &cmdJoin},
    {"PRIVMSG", &cmdPrivmsg},
};

void CommandDispatcher::dispatch(IRCCore& core, User& user, const Message& msg)
{
    if (msg.command.empty())
        return;
    std::string cmd = msg.command;
    for (size_t i = 0; i < cmd.size(); ++i)
        cmd[i] = std::toupper(cmd[i]);
    std::map<std::string, CommandFn>::iterator it = g_commands.find(cmd);
    if (it == g_commands.end()) {
        user.send(ERR_UNKNOWNCOMMAND(user.getNick(), cmd));
        return ;
    }
    it->second(core, user, msg);
}
