#pragma once
#include <string>

class User {
public:
    User();

    // Identity (RFC)
    const std::string& getNick() const;
    const std::string& getUser() const;
    const std::string& getRealName() const;

    void setNick(const std::string& nick);
    void setUser(const std::string& user);
    void setRealName(const std::string& realname);

    // Registration
    bool isRegistered() const;
    bool canRegister() const;
    void setRegistered(bool value);

    // Operator
    bool isOperator() const;
    void setOperator(bool value);

private:
    std::string _nick;
    std::string _user;
    std::string _realname;

    bool _registered;
    bool _isOperator;
};

