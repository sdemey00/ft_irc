/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemey <sdemey@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:35:13 by sdemey            #+#    #+#             */
/*   Updated: 2025/12/16 16:35:15 by sdemey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"

bool	IRCCore::nickExists(const std::string& nick) const {
    return _users.find(nick) != _users.end();
}

// Channel* IRCCore::getOrCreateChannel(const std::string& name)
// {
//     if (channels.count(name) == 0)
//         channels[name] = new Channel(name);
//     return channels[name];
// }
