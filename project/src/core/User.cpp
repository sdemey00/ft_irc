#include "User.hpp"

User::User()
    : _registered(false), _isOperator(false) {}

bool User::isRegistered() const {
    return _registered;
}

bool User::canRegister() const {
    return !_nick.empty() && !_user.empty();
}

void User::setRegistered(bool value) {
    _registered = value;
}

bool User::isOperator() const {
    return _isOperator;
}

void User::setOperator(bool value) {
    _isOperator = value;
}
