# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 17:44:49 by ztisnes           #+#    #+#              #
#    Updated: 2019/02/21 17:42:39 by ztisnes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# COLORS                                                                       #
################################################################################

RES = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
LCYAN = \033[1;36m
CYAN = \033[1;34m
PURPLE = \033[0;35m

################################################################################
# INITIAL FORMAT OR COMPILATION                                                #
################################################################################

CC			= gcc
FLAGS		= -Ofast -Wextra -Wall -Werror
LIB			= libft.a
NAME		= lem-in
LINK		= -L libft/ -l ft
INC			= -I inc/ -I libft/libft.h
SRCFILES	= $(wildcard *.c)
SRCDIR		= src/
OBJS		= $(patsubst %, %.o, $(addprefix $(SRCDIR), $(SRCFILES)))

SRCFILES	= bfs

################################################################################
# RULES                                                                        #
################################################################################

all: $(LIB) $(NAME)
	@ echo " $(GREEN) Completed $(RES)"

$(LIB):
	make -C libft/

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INC) $(OBJS) $(LINK) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	/bin/rm -f src/*.o
	/bin/rm -f $(OBJSRC)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft/$(LIB)
	@ echo "👺🖕$(RED) ALL Binaries gone!$(RES) 👺🖕"

re: fclean all
	@ echo "$(GREEN)♻️ Program remade completed ♻️$(RES)"

.PHONY: all clean fclean
