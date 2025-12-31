#!/usr/bin/env bash

# =========================
# IRC Server Test Script
# =========================

SERVER="127.0.0.1"
PORT="6667"
TIMEOUT=2

PASS="PASS pass"
NICK="NICK testuser"
USER="USER testuser 0 * :Test User"
CHANNEL="#testchan"

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

fail() {
    echo -e "${RED}[FAIL] $1${NC}"
}

pass() {
    echo -e "${GREEN}[PASS] $1${NC}"
}

run_test() {
    NAME="$1"
    COMMANDS="$2"
    EXPECT="$3"

    OUTPUT=$(echo -e "$COMMANDS" | nc -w $TIMEOUT $SERVER $PORT)

    if echo "$OUTPUT" | grep -q "$EXPECT"; then
        pass "$NAME"
    else
        fail "$NAME"
        echo "Expected: $EXPECT"
        echo "Got:"
        echo "$OUTPUT"
    fi
}

echo "=============================="
echo " IRC SERVER TESTS"
echo " Server: $SERVER:$PORT"
echo "=============================="

# Register user
run_test "User registration (NICK/USER)" \
"$PASS\r\n$NICK\r\n$USER\r\n" \
"001 testuser"

# Ping / Pong
run_test "PING / PONG" \
"$PASS\r\n$NICK\r\n$USER\r\nPING :hello\r\n" \
"PONG"

# Join channel
run_test "JOIN channel" \
"$PASS\r\n$NICK\r\n$USER\r\nJOIN $CHANNEL\r\n" \
"JOIN $CHANNEL"

# Send PRIVMSG
run_test "PRIVMSG in channel" \
"$PASS\r\n$NICK\r\n$USER\r\nJOIN $CHANNEL\r\nPRIVMSG $CHANNEL :Hello world\r\n" \
"PRIVMSG $CHANNEL"

# Invalid command handling
run_test "Unknown command error" \
"$PASS\r\n$NICK\r\n$USER\r\nFOOBAR\r\n" \
"421"

echo "=============================="
echo " Tests completed"
echo "=============================="
