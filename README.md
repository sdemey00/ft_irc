*This project has been created as part of the 42 curriculum by mmichele and sdemey.*

*~150h*

# ft_irc

IRC server in C++98, compatible with a standard IRC client.

---

## Table of contents

- [Description](#description)
  - [Change channel permissions with `MODE` command](#change-channel-permissions-with-mode-command)
- [Installing](#installing)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
- [Quick Start](#quick-start)
- [Usage](#usage)
- [Example Session](#example-session)
- [IRC Bot](#irc-bot)
- [Ressources](#ressources)
  - [Usage of AI](#usage-of-ai)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Description

ft_irc is a minimal implementation of an IRC (Internet Relay Chat) server written in C++98.

The objective of the project is to understand and implement the fundamentals of:
- network programming
- socket communication
- client/server architecture
- IRC protocol behavior

The implementation is compatible with the following commands :

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

This project was designed to respect the constraints of the 42 curriculum, including:

- using C++98
- avoiding external libraries
- implementing core IRC features from scratch.

---

## Installing

### Prerequisites

- Linux-based system
- GCC compiler
- Make
- X11 development libraries

Installing reference client : `sudo apt install irssi`

### Build

The project is compiled with **GCC** and the standard C flags: **-Wall -Wextra -Werror**
```sh
# Clone the repository
git clone https://github.com/sdemey00/ft_irc.git
cd ft_irc

# Compile the project
make
```

```sh
# Cleaning
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild from scratch
```
---

## Quick Start

```bash
git clone https://github.com/sdemey00/ft_irc.git
cd ft_irc
make
./ircserv 6667 password
```

## Usage
Start server:

```bash
./ircserv <port> <password>
```

Optional bot:
```bash
./ircbot <address> <port> <password> <name>
```
---
### Example Session

Example using irssi:
```
/connect localhost 6667 password
/nick alice
/join #42
```

Send message:
```
Hello everyone!
```

Operator commands:
```
/mode #42 +i
/invite bob #42
/kick bob
```

---

## IRC Bot

The project includes a simple IRC bot that can connect to the server and respond to commands.
The bot can be invited to a channel or through private messages.


Start the bot with:

```bash
./ircbot <address> <port> <password> <name>
```


It listens for specific commands:
| Command | Description                  |
|--------|------------------------------|
| `!toss`    | Toss a coin and return **Heads** or **Tails** |
| `!roll`    | Roll a dice and return a random number between **1 and 6** |

### Exemple

```bash
./ircbot localhost 6667 password bot42
```

Once connected, the bot can be invited to a channel:

```
/invite bot42 #42
```

Users can then interact with it using commands.
```
!roll
bot42: 4

!toss
bot42: Heads
```

---

## Ressources
| IRC (Internet Relay Chat)                          | Irssi (reference client)                                        | C++                                                |
|----------------------------------------------------|-----------------------------------------------------------------|----------------------------------------------------|
| [Wikipedia](https://en.wikipedia.org/wiki/IRC)     | [Wikipedia](https://en.wikipedia.org/wiki/Irssi)                | [cppreference.com](https://en.cppreference.com/w/) |
| [RFC 1459](https://www.rfc-editor.org/rfc/rfc1459) | [Documentation](https://irssi.org/documentation/#documentation) | [cplusplus.com](https://cplusplus.com/)            |

### Usage of AI
Helping creating bash scripts for testing.

---

## License

This project is part of the 42 School curriculum and is 42 property.

---

## Acknowledgments
- [42 School](https://42.fr/) for the project specifications
