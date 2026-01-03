#!/usr/bin/env bash

HOST=${1:-localhost}
PORT=${2:-6667}

NICK="tester$$"
CHAN="#breakme"

CRLF=$'\r\n'

send() {
  printf "%s${CRLF}" "$1"
}

echo "=== IRC BREAKER ==="
echo "Target: $HOST:$PORT"
echo

#######################################
# 1. Baseline valid connection
#######################################
(
send "PASS pass"
send "NICK $NICK"
send "USER $NICK 0 * :Test User"
sleep 1
send "JOIN $CHAN"
send "PRIVMSG $CHAN :hello world"
sleep 1
send "QUIT :done"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 2. Registration errors
#######################################
(
send "USER noNick 0 * :fail"
send "NICK"
send "USER"
send "NICK test"
send "NICK test"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 3. Commands before registration
#######################################
(
send "JOIN $CHAN"
send "PRIVMSG $CHAN :oops"
send "MODE $CHAN"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 4. Channel edge cases
#######################################
(
send "PASS pass"
send "NICK chanTest"
send "USER chanTest 0 * :chan"
sleep 1
send "JOIN"
send "JOIN #"
send "JOIN #doesnotexist"
send "PART"
send "PART #doesnotexist"
send "TOPIC"
send "TOPIC #doesnotexist"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 5. PRIVMSG torture
#######################################
(
send "PASS pass"
send "NICK msgTest"
send "USER msgTest 0 * :msg"
sleep 1
send "JOIN $CHAN"
send "PRIVMSG"
send "PRIVMSG :"
send "PRIVMSG $CHAN"
send "PRIVMSG nonexistent :hi"
send "PRIVMSG $CHAN :😀🔥💥"
send "PRIVMSG $CHAN :こんにちは"
send "PRIVMSG $CHAN :$(printf 'A%.0s' {1..500})"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 6. MODE abuse
#######################################
(
send "PASS pass"
send "NICK modeTest"
send "USER modeTest 0 * :mode"
sleep 1
send "JOIN $CHAN"
send "MODE"
send "MODE #"
send "MODE $CHAN +m"
send "MODE $CHAN +oooooooooooooooo"
send "MODE $CHAN +o nonexistent"
send "MODE modeTest +i"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 7. Unknown & malformed commands
#######################################
(
send "PASS pass"
send "NICK weird"
send "USER weird 0 * :weird"
sleep 1
send "FOOBAR"
send "HELLO WORLD"
send "THISISNOTACOMMAND"
send "PR1VMSG $CHAN :leet"
send "JOIN#test"
send "NICK=bad"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 8. Prefix abuse
#######################################
(
send "PASS pass"
send "NICK prefix"
send "USER prefix 0 * :prefix"
sleep 1
send ":fakeprefix PRIVMSG $CHAN :hello"
send "::doubleprefix PRIVMSG $CHAN :hello"
send ": PRIVMSG $CHAN :empty"
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 9. CRLF / whitespace weirdness
#######################################
(
send "PASS pass"
send "NICK spaced"
send "USER spaced 0 * :space test"
sleep 1
printf "PRIVMSG ${CHAN} :hi${CRLF}${CRLF}${CRLF}"
printf "QUIT${CRLF}"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 10. Binary junk
#######################################
(
send "PASS pass"
send "NICK junkTest"
send "USER junkTest 0 * :junk"
sleep 1
cat /dev/urandom | head -c 200
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 11. Oversized payload
#######################################
(
send "PASS pass"
send "NICK longnick"
send "USER longnick 0 * :long"
sleep 1
python3 - << EOF
print("PRIVMSG $CHAN :" + "A"*5000)
print("QUIT")
EOF
) | nc -q 1 "$HOST" "$PORT"

#######################################
# 12. Rapid-fire spam
#######################################
(
send "PASS pass"
send "NICK spammer"
send "USER spammer 0 * :spam"
sleep 1
send "JOIN $CHAN"
for i in {1..1000}; do
  send "PRIVMSG $CHAN :spam $i"
done
send "QUIT"
) | nc -q 1 "$HOST" "$PORT"

echo
echo "=== DONE ==="
