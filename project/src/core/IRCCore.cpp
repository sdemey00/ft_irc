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

IRCCore::~IRCCore() {
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        delete it->second;
    }
    _channels.clear();
    // for (std::map<std::string, User*>::iterator it = _users.begin(); it != _users.end(); ++it) {
    //     delete it->second;
    // }
    // _users.clear();
}

bool	IRCCore::nickExists(const std::string& nick) const {
    return (_users.find(nick) != _users.end()); //find return map.end() if not found
}

User*   IRCCore::getUserByNick(const std::string& nick) {
    if (!nickExists(nick))
        return (NULL);
    return (_users[nick]);
}

Channel*    IRCCore::getChannel(const std::string& name) {
    if (_channels.count(name) == 0)
        return (NULL);
    return (_channels[name]);
}

Channel*    IRCCore::getOrCreateChannel(const std::string& name) {
    if (_channels.count(name) == 0)
        _channels[name] = new Channel(name);
    return (_channels[name]);
}
