# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 10:59:54 by mmichele          #+#    #+#              #
#    Updated: 2025/12/21 03:33:51 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source program name
NAME	= ircserv

# Source program compiler settings
CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98

# Directories
BLDD	= build
SRCD	= src
INCD	= includes

# Source compile variables
SRCS	= $(shell find $(SRCD) -type f -name "*.cpp")
OBJS	= $(patsubst %.cpp, $(BLDD)/%.o, $(SRCS))
INCS	= -I $(SRCD) -I $(INCD)
LNKS	=
LIBS	=
DEPS	= $(OBJS:.o=.d)

# Fake targets
.PHONY: clean fclean re debug san valgrind gdb

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@ $(INCS) $(LNKS) $(LIBS)

$(BLDD)/%.o: %.cpp
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) -MMD -MP -c $< -o $@ $(INCS)

-include $(DEPS)

clean:
	rm -rf $(BLDD)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: FLAGS += -g
debug: all

san: FLAGS += -fsanitize=address,leak,undefined
san: debug all

# Following targets allow makefile variables PORT and PASS to be set.
PORT	?= 6667
PASS	?= pass

valgrind: debug
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./$(NAME) $(PORT) $(PASS)

gdb: debug
	gdb --tui --args "$(NAME)" $(PORT) $(PASS)
