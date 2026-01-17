# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 10:59:54 by mmichele          #+#    #+#              #
#    Updated: 2026/01/03 14:49:11 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98

# Directories
BLDD	= build
SRCD	= src
INCD	= includes
TSTD	= test
LOGD	= logs

$(shell mkdir -p $(LOGD))

################################################################################
# Overall targets                                                              #
################################################################################

S_NAME	= ircserv
B_NAME	= ircbot

all: $(S_NAME) $(B_NAME)

# Fake targets
.PHONY: clean fclean re debug san valgrind valgrind-bot gdb gdb-bot test

clean:
	rm -rf $(BLDD)
	rm -rf $(LOGD)

fclean: clean
	rm -rf $(S_NAME) $(B_NAME)

re: fclean all

debug: FLAGS += -g
debug: all

san: FLAGS += -fsanitize=address,leak,undefined
san: debug all

# Following targets allow makefile variables PORT and PASS to be set.
PORT	?= 6667
PASS	?= pass
ADDR	?= 127.0.0.1
BOTN	?= bot

valgrind: debug
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --log-file=$(LOGD)/valgrind-$(S_NAME).log ./$(S_NAME) $(PORT) $(PASS)

valgrind-bot: debug
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --log-file=$(LOGD)/valgrind-$(B_NAME).log ./$(B_NAME) $(ADDR) $(PORT) $(PASS) $(BOTN)

gdb: debug
	gdb --tui --args "$(S_NAME)" $(PORT) $(PASS)

gdb-bot: debug
	gdb --tui --args "$(B_NAME)" $(ADDR) $(PORT) $(PASS) $(BOTN)

test:
	bash $(TSTD)/test.sh

################################################################################
# Common files                                                                 #
################################################################################

# Directories
COMD	= common
C_BLDD	= $(BLDD)/$(COMD)
C_SRCD	= $(SRCD)/$(COMD)
C_INCD	= $(INCD)/$(COMD)

# Compile variables
C_SRCS	= src/common/Errors.cpp\
	src/common/core/cmd/cmdInvite.cpp\
	src/common/core/cmd/cmdJoin.cpp\
	src/common/core/cmd/cmdKick.cpp\
	src/common/core/cmd/cmdNick.cpp\
	src/common/core/cmd/cmdPart.cpp\
	src/common/core/cmd/cmdPass.cpp\
	src/common/core/cmd/cmdPing.cpp\
	src/common/core/cmd/cmdPrivmsg.cpp\
	src/common/core/cmd/cmdQuit.cpp\
	src/common/core/cmd/cmdTopic.cpp\
	src/common/core/cmd/cmdUser.cpp\
	src/common/core/cmd/cmdMode.cpp\
	src/common/core/Channel.cpp\
	src/common/core/IRCCore.cpp\
	src/common/core/Message.cpp\
	src/common/core/User.cpp\
	src/common/Log.cpp\
	src/common/Requestable.cpp\
	src/common/sighandler.cpp\
	src/common/utils.cpp
C_OBJS	= $(patsubst %.cpp, $(C_BLDD)/%.o, $(C_SRCS))
C_INCS	= -I $(C_INCD) #-I $(C_INCD)/core
C_DEPS	= $(C_OBJS:.o=.d)

$(C_BLDD)/%.o: %.cpp
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) -MMD -MP -c $< -o $@ $(C_INCS)

-include $(C_DEPS)

################################################################################
# IRC Server                                                                   #
################################################################################

# Directories
SERD	= server
S_BLDD	= $(BLDD)/$(SERD)
S_SRCD	= $(SRCD)/$(SERD)
S_INCD	= $(INCD)/$(SERD)

# Compile variables
S_SRCS	= src/server/main.cpp\
	src/server/Client.cpp\
	src/server/Server.cpp
S_OBJS	= $(C_OBJS) $(patsubst %.cpp, $(S_BLDD)/%.o, $(S_SRCS))
S_INCS	= $(C_INCS) -I $(S_INCD)
S_DEPS	= $(S_OBJS:.o=.d)

$(S_NAME): $(S_OBJS)
	$(CC) $(FLAGS) $^ -o $@ $(S_INCS)

$(S_BLDD)/%.o: %.cpp
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) -MMD -MP -c $< -o $@ $(S_INCS)

-include $(S_DEPS)

################################################################################
# IRC Bot                                                                      #
################################################################################

# Directories
BOTD	= bot
B_BLDD	= $(BLDD)/$(BOTD)
B_SRCD	= $(SRCD)/$(BOTD)
B_INCD	= $(INCD)/$(BOTD)

# Compile variables
B_SRCS	= src/bot/RNG.cpp\
	src/bot/Command.cpp\
	src/bot/Client.cpp\
	src/bot/main.cpp
B_OBJS	= $(C_OBJS) $(patsubst %.cpp, $(B_BLDD)/%.o, $(B_SRCS))
B_INCS	= $(C_INCS) -I $(B_INCD)
B_DEPS	= $(B_OBJS:.o=.d)

$(B_NAME): $(B_OBJS)
	$(CC) $(FLAGS) $^ -o $@ $(B_INCS)

$(B_BLDD)/%.o: %.cpp
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) -MMD -MP -c $< -o $@ $(B_INCS)

-include $(B_DEPS)
