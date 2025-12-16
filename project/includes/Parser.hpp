#pragma once
#include "Message.hpp"
#include <string>

class Parser {
public:
    static Message parse(const std::string& line);
};