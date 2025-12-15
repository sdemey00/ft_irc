#pargma once

class Message {
	public:
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;
}

//	[:prefix] COMMAND param1 param2 :trailing
// <message> ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
// <prefix> ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
// <command> ::= <letter> { <letter> } | <number> <number> <number>
// <SPACE> ::= ' ' { ' ' }
// <params> ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
// <middle> ::= <Any *non-empty* sequence of octets not including SPACE
//  or NUL or CR or LF, the first of which may not be ':'>
// <trailing> ::= <Any, possibly *empty*, sequence of octets not including
//  NUL or CR or LF>
// <crlf> ::= CR LF
