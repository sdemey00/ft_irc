#pragma once

#define CRLF "\r\n"

///////// REPLIES ///////////////
#define RPL_WELCOME(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_TOPIC(channel, topic) (": 332 " + channel + " : " + topic + CRLF)
#define RPL_INVITING(channel, nickname) (": 341 " + channel + " " + nickname + CRLF)

///////// ERRORS ////////////////
#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_NONICKNAMEGIVEN(nickname) (": 431 " + nickname + " :No nickname given")
#define ERR_NEEDMOREPARAMS(cmd) (": 461 " + cmd + " :Not enough parameters" + CRLF)
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (": 421 " + nickname + " " + cmd + " :Unknown command" + CRLF)



// :irc.example.com 433 currentNick foo :Nickname is already in use
//
// inline std::string ERR_NICKNAMEINUSE(const std::string& currentNick,
//                                     const std::string& requestedNick,
//                                     const std::string& server)
// {
//     return ":" + server + " 433 " + currentNick + " " +
//            requestedNick + " :Nickname is already in use\r\n";
// }
// complete implementation
// inline std::string ERR_NICKNAMEINUSE(
//     const std::string& currentNick,
//     const std::string& newNick,
//     const std::string& server)
// {
//     return ":" + server + " 433 " +
//            (currentNick.empty() ? "*" : currentNick) +
//            " " + newNick +
//            " :Nickname is already in use\r\n";
// }