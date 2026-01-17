# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ddos.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/02 13:56:02 by mmichele          #+#    #+#              #
#    Updated: 2026/01/02 14:50:09 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ADDR="10.1.1.4"
PORT=6667
PASS="pass"
BASE_NICK="testuser"
CLIENTS=1000

for i in $(seq 1 "$CLIENTS"); do
(
  NICK="${BASE_NICK}${i}"

  printf "PASS %s\r\n" "$PASS"
  printf "NICK %s\r\n" "$NICK"
  printf "USER %s 0 * :%s\r\n" "$NICK" "$NICK"
) | nc -w 1 "$ADDR" "$PORT" &

done

wait
