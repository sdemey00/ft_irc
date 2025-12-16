#pragma once

#define CRLF "\r\n"

///////// REPLIES ///////////////
#define RPL_WELCOME(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_TOPIC(channel, topic) (": 332 " + channel + " : " + topic + CRLF)
#define RPL_INVITING(channel, nickname) (": 341 " + channel + " " + nickname + CRLF)

///////// ERRORS ////////////////
#define ERR_NICKINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_NEEDMOREPARAMS(cmd) (": 461 " + cmd + " :Not enough parameters" + CRLF)
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (": 421 " nickname + " " + cmd + " :Unknown command" + CRLF)
