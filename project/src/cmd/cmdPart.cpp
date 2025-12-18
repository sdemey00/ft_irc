/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:44 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:45 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

//       Command: PART
//    Parameters: <channel>{,<channel>}

// void    IRCCore::cmdPart(User& user, const Message& msg) {}

//    The PART message causes the client sending the message to be removed
//    from the list of active users for all given channels listed in the
//    parameter string.

//    Numeric Replies:
//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_NOTONCHANNEL

//    Examples:
//    PART #twilight_zone             ; leave channel "#twilight_zone"
//    PART #oz-ops,&group5            ; leave both channels "&group5" and
//                                    "#oz-ops".
