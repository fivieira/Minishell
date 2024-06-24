# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 15:06:49 by ndo-vale          #+#    #+#              #
#    Updated: 2024/06/24 19:34:03 by ndo-vale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g 
IFLAGS	= -lreadline
RM	= rm -rf

SRC_DIR		= src/
OBJ_DIR		= obj/
SRCS		= $(addprefix $(SRC_DIR), main.c get_token.c)
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -s clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
