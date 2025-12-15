#include "Channel.hpp"

Channel::Channel() : name("") {}
Channel::Channel(std::string n) : name(n) {}
Channel::~Channel() {}

void	Channel::join(User *c) {
	// add user to channel
	_members += c;
}

void	Channel::part(User *c) {
	// remove user from channel
	_members -= c;
}

bool	isOperator(User *c) {
	for (int i = 0; i < _operators.lenght(); i++) {
		if (_operators[i] == c)
			return (true);
	}
	return (false);
}
