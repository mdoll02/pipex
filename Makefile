# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 09:23:42 by mdoll             #+#    #+#              #
#    Updated: 2023/02/10 10:02:10 by mdoll            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

SRCS	:=	mandatory/pipex.c mandatory/pipex_utils.c

OBJS	:= $(SRCS:.c=.o)

BONUS_SRCS	:=	bonus/pipex_bonus.c bonus/pipex_utils_bonus.c

BONUS_OBJS	:= $(BONUS_SRCS:.c=.o)

RM		:= rm -f

b	=	\033[1;30m
r	=	\033[1;31m
g	=	\033[1;32m
y	=	\033[1;33m
bl	=	\033[1;34m
p	=	\033[1;35m
c	=	\033[1;36m
w	=	\033[1;37m
end =	[0m

%.o: %.c
	@ $(CC) -c $(CFLAGS) $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@ echo "${r}compiling${end}"
	@ make all -C ./libft >/dev/null 2>&1
	@ cp ./libft/libft.a .
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft.a
	@ echo "${g}finished compiling.${end}"
	@ echo "${bl}Use: ./pipex file1 cmd1 cmd2 file2 to run the progam${end}"

all:	${NAME}

bonus: ${BONUS_OBJS}
	@ echo "${r}compiling${end}"
	@ make all -C ./libft >/dev/null 2>&1
	@ cp ./libft/libft.a .
	@ $(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) libft.a
	@ echo "${g}finished compiling.${end}"
	@ echo "${bl}Use: ./pipex file1 cmd1 cmd2 ... file2 to run the progam${end}"

clean:
	@${RM} $(OBJS)
	@${RM} $(BONUS_OBJS)
	@make clean -C ./libft
	@ echo "${y}cl${bl}ea${p}ne${c}d!${end}"

fclean:
	@ ${RM} ${NAME}
	@ make fclean -C ./libft
	@ ${RM} libft.a
	@ echo "${y}eve${bl}ryt${p}hi${c}ng${end}"
	@ make clean

files: all
	@ ${RM} *.txt
	@ touch input
	@ touch output

re:			fclean all

.PHONY:		all clean fclean re files bonus