# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 13:55:48 by rpires-c          #+#    #+#              #
#    Updated: 2025/03/06 11:24:17 by rpires-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler flags
FLGS = -Wall -Wextra -Werror
VAL = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes

# Commands
CC = cc -g
RM = rm -f

# Supress makefile messages
MAKEFLAGS += -s

# Source files
SRCS = src/philo.c src/parser.c src/initializer.c src/philo_utils.c \
	src/thread_mutex_handlers.c src/setters.c src/getters.c src/simulation.c \
	src/sleep_eat_think.c
# Object files
OBJDIR = Objs
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

# Output
NAME = philo

# Create object directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Main target
$(NAME): $(OBJS)
	@$(CC) $(FLGS) $(OBJS) -o $(NAME)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Compiled Successfully!║"
	@echo "╚══════════════════════════╝"

# Compile all source files
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(FLGS) -o $@ $<

# Phony targets
.PHONY: all clean fclean re exec norm normi

all: $(NAME)

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

n:
	norminette $(SRCS)

s:
	clear && make re

v:
	$(VAL) ./philo 

g:
	gdb -tui ./philo --args 
