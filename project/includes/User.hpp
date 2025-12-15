#pragma once

class User {			//Client
	public:
	int	fd;
	// RFC identity
	std::string	nickname;
	std::string	username;
	std::string	name;

	//password
	bool registered;

	std::string readBuff;

	void	send(std::string &msg);
}
