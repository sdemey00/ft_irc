// #include "CmdDispatch.hpp"

// void cmdJoin(IRCCore& core, User& user, const Message& msg)
// {
//     if (!user.isRegistered()) {
//         user.send(ERR_NOTREGISTERED());
//         return;
//     }
//     if (msg.params.empty()) {
//         user.send(ERR_NEEDMOREPARAMS("JOIN"));
//         return;
//     }
//     const std::string& chanName = msg.params[0];
//     if (chanName[0] != '#') {
//         user.send(ERR_NOSUCHCHANNEL(chanName));
//         return;
//     }
//     Channel* channel = core.getOrCreateChannel(chanName);
//     if (channel->hasUser(&user))
//         return;
//     channel->addUser(&user);
//     //user.joinChannel(channel);
//     // JOIN reply
//     user.send(":" + user.getNick() + " JOIN " + chanName);
//     // NAMES
//     std::string names;
//     const std::set<User*>& users = channel->getUsers();
//     for (std::set<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
//         if (!names.empty())
//             names += " ";
//         names += (*it)->getNick();
//     }
//     user.send(RPL_NAMREPLY(user.getNick(), chanName, names));
//     user.send(RPL_ENDOFNAMES(user.getNick(), chanName));
// }