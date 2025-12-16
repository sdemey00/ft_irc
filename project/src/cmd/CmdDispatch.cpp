/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdDispatch.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:34:25 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:34:27 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdDispatch.hpp"

typedef void (*CommandFn)(IRCCore&, User&, const Message&);

static std::map<std::string, CommandFn> initCommands()
{
    std::map<std::string, CommandFn> cmds;
    cmds["NICK"] = &cmdNick;
    // cmds["USER"] = &cmdUser;
    // cmds["JOIN"] = &cmdJoin;
    // cmds["PART"] = &cmdPart;
    // cmds["PRIVMSG"] = &cmdPrivmsg;
	// cmds["NOTICE"] = &cmdNotice;
	// cmds["QUIT"] = &cmdQuit;
	// cmds["PING"] = &cmdPing;
	// operators cmd (channel):
	// cmds["KICK"] = &cmdKick;
	// cmds["INVITE"] = &cmdInvite;
	// cmds["TOPIC"] = &cmdTopic;
	// cmds["MODE"] = &cmdMode;
    return (cmds);
}

static std::map<std::string, CommandFn> g_commands = initCommands();

void CommandDispatcher::dispatch(IRCCore& core, User& user, const Message& msg)
{
    std::string cmd = msg.command;
    if (cmd.empty())
        return ;
    for (size_t i = 0; i < cmd.size(); ++i)
        cmd[i] = std::toupper(cmd[i]);
    std::map<std::string, CommandFn>::iterator it = g_commands.find(cmd);
    if (it == g_commands.end()) {
        user.send(ERR_UNKNOWNCOMMAND(user.getNick(), cmd));
        return ;
    }
    it->second(core, user, msg);
}
