# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcherret <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 12:35:44 by tcherret          #+#    #+#              #
#    Updated: 2019/03/01 15:13:06 by tcherret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

NAMELIB = ./libft/libftprintf.a

CC = @gcc

CFLAGS =-Wall -Wextra -Werror -g

SRCS = srcs/lem_in.c\
	   srcs/parsing0.c\
	   srcs/parsing1.c\
	   srcs/parsing_checker.c\
	   srcs/ft_realloc_room.c\
	   srcs/get_option.c\
	   srcs/bfs.c\
	   srcs/queue_function.c\
	   srcs/ant_function.c\
	   srcs/free_functions.c\


INCS = lem_in.h

LIBDIR = ./libft/
INCDIR = ./includes/

OBJ = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ)
		@echo "\033[33mCompiling...\033[0m"
		@make -C $(LIBDIR)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(NAMELIB)
		@echo "\033[32m$(NAME) compiled ✔ ✔ ✔ ✔\033[0m"

objs/%.o : srcs/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -I./includes -o $@

clean :
		@rm -rf $(OBJ) objs
		@make -C $(LIBDIR) clean
		@echo "\033[31mObjects deleted ✕\033[0m"

fclean : clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean
	@echo "\033[31m$(NAME) deleted ✕\033[0m"

re : fclean all

git: fclean
	git add *
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re
