/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdDispatch.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:35:12 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/18 12:35:13 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include "Replies.hpp"
#include "Errors.hpp"
#include "Message.hpp"
#include "IRCCore.hpp"
#include "Channel.hpp"
#include "User.hpp"

// cmd list prototype
void cmdNick(IRCCore& core, User& user, const Message& msg);
//void cmdUser(IRCCore& core, User& user, const Message& msg);
//void cmdJoin(IRCCore& core, User& user, const Message& msg);

class CmdDispatch {
public:
    static void dispatch(IRCCore& core, User& user, const Message& msg);
};
