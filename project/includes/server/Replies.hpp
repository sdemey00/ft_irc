/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:20 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/19 12:55:07 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CRLF "\r\n"

///////// REPLIES ///////////////
#define RPL_WELCOME(nickname) (":ft_irc 001 " + nickname + " : Welcome to the FT_IRC server!" + CRLF)
#define RPL_NICK(oldnick, newnick) (":" + oldnick + " NICK :" + newnick + CRLF)
#define RPL_PRIVMSG(nick, user, host, target, text) (":" + nick + "!" + user + "@" + host + " PRIVMSG " + target + " :" + text + CRLF)
#define RPL_JOIN(nick, channel) (":ft_irc " + nick + " JOIN " + channel + CRLF)
#define RPL_PART(nick, user, host, channel) (":" + nick + "!" + user + "@"+ host + " PART " + channel + " :" + CRLF)
#define RPL_TOPIC(channel, topic) (":ft_irc 332 " + channel + " : " + topic + CRLF)
#define RPL_INVITING(channel, nickname) (":ft_irc 341 " + channel + " " + nickname + CRLF)
#define RPL_NAMREPLY(nick, symbol, channel, names) (":ft_irc 353 " + nick + " " + symbol + " " + channel + " :" + names + CRLF)
#define RPL_ENDOFNAMES(nick, channel) (":ft_irc 366 " + nick + " " + channel + " :End of /NAMES list" + CRLF)

///////// ERRORS ////////////////
#define ERR_NOSUCHNICK(nickname) (":ft_irc 401 " + nickname + " :No such nick/channel" + CRLF)
#define ERR_NOSUCHCHANNEL(channel) (":ft_irc 403 " + channel + " :No such channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN(channel) (":ft_irc 404 " + channel + " :Cannot send to channel" + CRLF)
#define ERR_NOTEXTTOSEND() (std::string(":ft_irc 412 :No text to send") + std::string(CRLF))
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (":ft_irc 421 " + nickname + " " + cmd + " :Unknown command" + CRLF)
#define ERR_NONICKNAMEGIVEN(nickname) (":ft_irc 431 " + nickname + " :No nickname given")
#define ERR_NICKNAMEINUSE(oldnick, newnick) (":ft_irc 433 " + oldnick + " " + newnick + " :Nickname is already in use" + CRLF)
#define ERR_NOTONCHANNEL(channel) ("ft_irc 442 " + channel + " :You're not on that channel" + CRLF)
#define ERR_NOTREGISTERED(nickname) (":ft_irc 451 " + nickname + " :You have not reregistered" + CRLF)
#define ERR_NEEDMOREPARAMS(cmd) (":ft_irc 461 " + cmd + " :Not enough parameters" + CRLF)
#define ERR_ALREADYREGISTRED(nickname) (":ft_irc 462 " + nickname + " :You may not reregister" + CRLF)

// :irc.example.com 433 currentNick foo :Nickname is already in use

// NAMREPLY symbols
// = -> canal public
// * -> canal privé
// @ -> canal secret

// = -> canal public
// @Sammy -> opérateur
// +Scooby -> voice
// Charlie -> utilisateur normal
