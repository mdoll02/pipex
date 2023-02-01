# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 09:23:42 by mdoll             #+#    #+#              #
#    Updated: 2023/02/01 09:35:03 by mdoll            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

SRCS	:=	src/pipex.c

OBJS	:= $(SRCS:.c=.o)

RM		    := rm -f

%.o: %.c
	@ $(CC) -c $(CFLAGS) $< -o ${<:.c=.o}

all:		${NAME}

$(NAME): $(OBJS)
	@ echo "\033[1;31mcompiling[0m"
	@ make all -C ./libft
	@ cp ./libft/libft.a .
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft.a
	@ echo "\033[1;32mfinished compiling.[0m"
	@ echo " "
	@ echo "\033[1;34mUse: ./pipex file1 cmd1 cmd2 file2 to run the progam[0m"

clean:
	@${RM} $(OBJS)
	@make clean -C ./libft

fclean:	clean
	@ ${RM} ${NAME}
	@ make fclean -C ./libft
	@ ${RM} libft.a

re:			fclean all

.PHONY:		all clean fclean re