# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    spambot.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/02 12:56:17 by mmichele          #+#    #+#              #
#    Updated: 2026/01/02 13:18:39 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ADDR="127.0.0.1"
PORT="6667"
PASS="pass"
NICK="spam"

LOGIN="PASS $PASS\r\nNICK $NICK\r\nUSER $NICK 0 * :$NICK"

COMMANDS="$LOGIN\r\n"

for i in {0..1000}
do
	COMMANDS+="PRIVMSG bot :!roll\r\n"
done

echo -e "$COMMANDS" | nc -w 3 $ADDR $PORT
