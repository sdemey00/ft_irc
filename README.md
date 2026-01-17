*This project has been created as part of the 42 curriculum by mmichele and sdemey.*
# ft_irc
IRC server in C++98, compatible with a standard IRC client.
## Table of contents
- [Description](#description)
	- [`MODE` command](#change-channel-permissions-with-mode-command)
- [Instructions](#instructions)
	- [Installing](#installing)
	- [Compiling](#compiling)
	- [Executing](#executing)
- [Ressources](#ressources)
	- [Usage of AI](#usage-of-ai)
## Description
Minimal implementation of an IRC server, compatible with the following commands :
| Command  | Params                                                   | Description                           |
|----------|----------------------------------------------------------|---------------------------------------|
|`PASS`    | `<password>`                                             | Connect to server with given password |
|`NICK`    | `<nickname>`                                             | Set nickname                          |
|`USER`    | `<username>` `<host name>` `<server name>` `<real name>` | Send user informations                |
|`JOIN`    | `<channel name>` `[password]`                            | Join/create channel                   |
|`PART`    | `<channel name>` `[message]`                             | Leave channel                         |
|`PRIVMSG` | `{user name, channel name}`                              | Send message                          |
|`QUIT`    | `[message]`                                              | Leave server                          |
|`PING`    | `[nickname]`                                             | Ping server or user                   |
|`KICK`    | `<nickname>` `[message]`                                 | Kick user from a channel              |
|`INVITE`  | `<nickname>` `<channel name>`                            | Invite user to a channel              |
|`TOPIC`   | `<channel name>` `[new topic]`                           | Change/get channel topic              |
|`MODE`    | `<channel name>` `{+, -}` `{i, t, k, o, l}`              | Change channel mode                   |
### Change channel permissions with `MODE` command
| Option | Params       | Description                  |
|--------|--------------|------------------------------|
| `i`    |              | Set/remove invite only       |
| `t`    |              | Set/remove topic restrict    |
| `k`    | `<password>` | Set/remove channel password  |
| `o`    | `<nickname>` | Give/take operator privilege |
| `l`    | `<limit>`    | Set/remove user limit        |
## Instructions
### Installing
Installing reference client : `sudo apt install irssi`
### Compiling
Compiling the project using _GNU Make_ :
```
make
```
### Executing
```
./ircserv <port> <password>  
./ircbot <address> <port> <password> <name>
```
## Ressources
| IRC (Internet Relay Chat)                          | Irssi (reference client)                                        | C++                                                |
|----------------------------------------------------|-----------------------------------------------------------------|----------------------------------------------------|
| [Wikipedia](https://en.wikipedia.org/wiki/IRC)     | [Wikipedia](https://en.wikipedia.org/wiki/Irssi)                | [cppreference.com](https://en.cppreference.com/w/) |
| [RFC 1459](https://www.rfc-editor.org/rfc/rfc1459) | [Documentation](https://irssi.org/documentation/#documentation) | [cplusplus.com](https://cplusplus.com/)            |
### Usage of AI
Helping creating bash scripts for testing.
