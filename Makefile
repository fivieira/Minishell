# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 15:06:49 by ndo-vale          #+#    #+#              #
#    Updated: 2024/07/22 23:30:21 by fivieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g 
IFLAGS	= -lreadline
RM	= rm -rf

SRC_DIR		= src/
OBJ_DIR		= obj/

SRCS		= $(addprefix $(SRC_DIR), main.c constructors.c free_tree.c exit.c exit_utils.c\
					tokenizer.c tokenlst_helpers.c 	tokenizer_helpers.c \
					tree_builder.c tree_executer.c tree_helpers.c \
					command_helpers.c signals.c signals_handlers.c \
					heredoc.c builtins/echo.c \
					builtins/pwd.c \
					builtins/export/ft_getenv.c \
					builtins/env.c)
					
#				continue to implement			

OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

MAKE = make -C

all: $(NAME)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@mkdir -p obj/builtins
	@mkdir -p obj/builtins/export
	@mkdir -p .tempfiles
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -s clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
