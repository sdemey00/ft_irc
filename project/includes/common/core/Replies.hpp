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
#define RPL_WELCOME(nickname) (":ft_irc 001 " + nickname + " : Welcome to the FT_IRC server, " + nickname + " !" + CRLF)
#define RPL_NICK(oldnick, newnick) (":" + oldnick + " NICK :" + newnick + CRLF)
#define RPL_PRIVMSG(prefix, target, text) (":" + prefix + " PRIVMSG " + target + " :" + text + CRLF)
#define RPL_JOIN(prefix, channel) (":" + prefix + " JOIN " + channel + CRLF)
#define RPL_PART(prefix, channel, reason) (":" + prefix + " PART " + channel + " :" + reason + CRLF)
#define RPL_TOPIC(nick, channel, topic) (":ft_irc 332 " + nick + " " + channel + " : " + topic + CRLF)
#define RPL_TOPICCHANGE(prefix, channel, topic) (":" + prefix + " TOPIC " + channel + " : " + topic + CRLF)
#define RPL_NOTOPIC(channel) (":ft_irc 331 " + channel + " :No topic is set" + CRLF)
#define RPL_KICK(prefix, channel, target, reason) (":" + prefix + " KICK " + channel + " " + target + " :" + reason + CRLF)
#define RPL_INVITING(inviter, target, channel) (":ft_irc 341 " + inviter + " " + target + " " + channel + CRLF)
#define RPL_INVITE(inviter, target, channel) (":" + inviter + " INVITE " + target + " :" + channel + CRLF)
#define RPL_NAMREPLY(nick, symbol, channel, names) (":ft_irc 353 " + nick + " " + symbol + " " + channel + " :" + names + CRLF)
#define RPL_ENDOFNAMES(nick, channel) (":ft_irc 366 " + nick + " " + channel + " :End of /NAMES list" + CRLF)
#define RPL_QUIT(prefix, reason) (":" + prefix + " QUIT :" + reason + CRLF)

///////// ERRORS ////////////////
#define ERR_NOSUCHNICK(nick, target) (":ft_irc 401 " + nick + " " + target + " :No such nick" + CRLF)
#define ERR_NOSUCHCHANNEL(channel) (":ft_irc 403 " + channel + " :No such channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN(channel) (":ft_irc 404 " + channel + " :Cannot send to channel" + CRLF) 
#define ERR_NORECIPIENT(nick, command) (":ft_irc 411 " + nick + " :No recipient given " + command + CRLF)
#define ERR_NOTEXTTOSEND() (std::string(":ft_irc 412 :No text to send") + std::string(CRLF))
#define ERR_UNKNOWNCOMMAND(nickname, cmd) (":ft_irc 421 " + nickname + " " + cmd + " :Unknown command" + CRLF)
#define ERR_NONICKNAMEGIVEN(nickname) (":ft_irc 431 " + nickname + " :No nickname given" + CRLF)
#define ERR_ERRONEUSNICKNAME(oldnick, newnick) (":ft_irc 432 " + oldnick + " " + newnick + " :Erroneous nickname" + CRLF)
#define ERR_NICKNAMEINUSE(oldnick, newnick) (":ft_irc 433 " + oldnick + " " + newnick + " :Nickname is already in use" + CRLF)
#define ERR_NOTONCHANNEL(channel) (":ft_irc 442 " + channel + " :You're not on that channel" + CRLF)
#define ERR_USERONCHANNEL(target, channel) (":ft_irc 443 " + target + " " + channel + " :is already on channel" + CRLF)
#define ERR_NOTREGISTERED(nickname) (":ft_irc 451 " + nickname + " :You have not registered" + CRLF)
#define ERR_NEEDMOREPARAMS(cmd) (":ft_irc 461 " + cmd + " :Not enough parameters" + CRLF)
#define ERR_ALREADYREGISTRED(nickname) (":ft_irc 462 " + nickname + " :You may not reregister" + CRLF)
#define	ERR_PASSWDMISMATCH(nickname) (":ft_irc 464 " + nickname + " :Password incorrect" + CRLF)
#define ERR_INVITEONLYCHAN(channel) (":ft_irc 473 " + channel + " :Cannot join channel (+i)" + CRLF)
#define ERR_CHANOPRIVSNEEDED(channel) (":ft_irc 482 " + channel + " :You're not channel operator" + CRLF)
#define ERR_CHANNELISFULL(channel) (":ft_irc 471 " + channel + " :Cannot join channel (+l)" + CRLF)
#define ERR_BADCHANMASK(nickname, channel) (":ft_irc 476 " + nickname + " " + channel + " :Bad Channel Mask" + CRLF)
#define ERR_BADCHANNELKEY(channel) (":ft_irc 475 " + channel + " :Cannot join channel (+k)" + CRLF)
#define ERR_USERNOTINCHANNEL(nick, channel) (":ft_irc 441 " + nick + " " + channel + " :They aren't on that channel" + CRLF)




