#pragma once
#include <map>
#include <string>

#include "User.hpp"
#include "Channel.hpp"

class IRCCore {
public:
    ~IRCCore(void);
    // Users
    bool    nickExists(const std::string& nick) const;
    User*   getUserByNick(const std::string& nick);

    // Channels
    Channel*    getChannel(const std::string& name);
    Channel*    getOrCreateChannel(const std::string& name);

private:
    std::map<std::string, User*>    _users;         // nick -> User
    std::map<std::string, Channel*> _channels;      // name -> Channel
                                                    // servername??
};
