CPPFLAGS =  -std=c++98 -Wall -Wextra -Werror
CC = g++
NAME = ircserv
BOT_NAME = Weather_bot
PREFIX = ./obj/
ASCII = \n\
██╗██████╗  ██████╗███████╗███████╗██████╗ ██╗   ██╗\n\
██║██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██║   ██║\n\
██║██████╔╝██║     ███████╗█████╗  ██████╔╝██║   ██║\n\
██║██╔══██╗██║     ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝\n\
██║██║  ██║╚██████╗███████║███████╗██║  ██║ ╚████╔╝ \n\
╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝ \n\
Contributors: ridwane, makram, kaoutar

SOURCE = src/commands/Nick.cpp \
         src/commands/Pass.cpp \
         src/commands/User.cpp \
         src/commands/Join.cpp \
         src/commands/Kick.cpp \
         src/commands/PrivMsg.cpp \
         src/commands/Part.cpp \
         src/commands/Quit.cpp \
         src/commands/Mode.cpp \
         src/commands/Invite.cpp \
         src/commands/Topic.cpp \
         src/commands/Weather.cpp \
         src/Client.cpp \
         src/CommandHandler.cpp \
         src/Replies.cpp \
         src/Server.cpp \
         src/channel.cpp \
         main.cpp

HEADERS = inc/Client.hpp \
          inc/channel.hpp \
          inc/Command.hpp \
          inc/CommandHandler.hpp \
          inc/Replies.hpp \
          inc/Server.hpp \
		  inc/ip_address.hpp

OBJECT = $(addprefix $(PREFIX), $(SOURCE:.cpp=.o))
BOT_SOURCE = bot/main.cpp
BOT_OBJECT = $(addprefix $(PREFIX), $(BOT_SOURCE:.cpp=.o))

COLOR = \033[1;32m
RESET = \033[0m
RED = \033[1;31m\033[1m


all: banner $(NAME) $(BOT_NAME)

banner:
	@echo "$(COLOR)$(ASCII)$(RESET)"

$(PREFIX):
	@mkdir -p $(PREFIX)src/commands
	@mkdir -p $(PREFIX)bot
	@echo "$(COLOR)Creating obj directory...$(RESET)"

# create the executable file
$(NAME): $(PREFIX) $(OBJECT)
	@echo "$(COLOR)Building $(NAME)$(RESET)"
	@$(CC) $(CPPFLAGS) $(OBJECT) -o $(NAME)
	@echo "$(COLOR)Build complete ✅$(RESET)"

$(BOT_NAME): $(PREFIX) $(BOT_OBJECT)
	@echo "$(COLOR)Building $(BOT_NAME)$(RESET)"
	@$(CC) $(CPPFLAGS) $(BOT_OBJECT) -o $(BOT_NAME)
	@echo "$(COLOR)Bot build complete ✅$(RESET)"

$(PREFIX)%.o: %.cpp $(HEADERS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(PREFIX)bot/%.o: bot/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "$(COLOR)Cleaning...$(RESET)"
	@rm -rf $(PREFIX)
	@rm -f $(OBJECT) $(BOT_OBJECT)
	@echo "$(COLOR)Clean complete ✅$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BOT_NAME) 

re: fclean all
.PHONY: all run clean fclean re banner