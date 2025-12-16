#pragma once
#include <map>
#include <string>

class User;
class Channel;

class IRCCore {
public:
    // Users
    bool nickExists(const std::string& nick) const;
    User* getUserByNick(const std::string& nick);

    // Channels
    Channel* getChannel(const std::string& name);
    Channel& getOrCreateChannel(const std::string& name);

private:
    std::map<std::string, User*> _users;        // nick -> User
    std::map<std::string, Channel> _channels;   // name -> Channel
												// servername
};
