#include "Channel.hpp"
#include "User.hpp"

Channel::Channel(const std::string& name)
    : _name(name) {}

void Channel::addUser(User* user) {
    _users.insert(user);
}

void Channel::removeUser(User* user) {
    _users.erase(user);
    _operators.erase(user);
}

bool Channel::hasUser(User* user) const {
    return _users.find(user) != _users.end();
}

void Channel::addOperator(User* user) {
    _operators.insert(user);
}

bool Channel::isOperator(User* user) const {
    return _operators.find(user) != _operators.end();
}

// first user to join become operator
