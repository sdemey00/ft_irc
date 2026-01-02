# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/02 12:56:08 by mmichele          #+#    #+#              #
#    Updated: 2026/01/02 12:56:09 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

ADDR="127.0.0.1"
PORT="6667"
PASS="pass"
NICK="test"

LOGIN="PASS $PASS\r\nNICK $NICK\r\nUSER $NICK 0 * :$NICK"
CHANNEL="#testChannel"

fail() {
	echo -e "${RED}[FAIL] $1${NC}"
}

pass() {
	echo -e "${GREEN}[PASS] $1${NC}"
}

test() {
	NAME="$1"
	COMMANDS="$2"
	EXPECT="$3"

	OUTPUT=$(echo -e "$COMMANDS" | nc -w 3 $ADDR $PORT)

	if echo "$OUTPUT" | grep -q "$EXPECT"; then
		pass "$NAME"
	else
		fail "$NAME"
		echo "Expected : $EXPECT"
		echo "Got :"
		echo "$OUTPUT"
	fi
}

echo "=============================="
echo " IRC SERVER TESTS"
echo " $ADDR:$PORT"
echo "=============================="

test "User registration (NICK/USER)" \
"$LOGIN\r\n" \
"001 $NICK"

test "Unregistered try" \
"JOIN $CHANNEL\r\n" \
"451"

test "PING / PONG" \
"$LOGIN\r\nPING\r\n" \
"PONG"

test "JOIN channel" \
"$LOGIN\r\nJOIN $CHANNEL\r\n" \
"JOIN $CHANNEL"

test "Unknown command error" \
"$LOGIN\r\nFOOBAR\r\n" \
"421"

test "Send DM to unknown user" \
"$LOGIN\r\nPRIVMSG idk: hello\r\n" \
"401"

./ircbot $ADDR $PORT $PASS bot 1>/dev/null &

sleep 1

test "Bot roll" \
"$LOGIN\r\nPRIVMSG bot :!roll\r\n" \
"bot PRIVMSG"

test "Bot toss" \
"$LOGIN\r\nPRIVMSG bot :!toss\r\n" \
"bot PRIVMSG"

test "Bot unknown" \
"$LOGIN\r\nPRIVMSG bot :!hello\r\n" \
"PRIVMSG $NICK :Unknown command"

echo "=============================="
echo " Tests completed"
echo "=============================="
