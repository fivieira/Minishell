# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 16:28:11 by ndo-vale          #+#    #+#              #
#    Updated: 2024/08/20 00:11:03 by fivieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc
CFLAGS	= -g -Wall -Werror -Wextra -c
NAME	= libft.a
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c ft_strldup.c ft_substr.c ft_strjoin.c \
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_strjoin_free.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_is_little_endian.c ft_strinvert.c ft_putnbr_base_fd.c get_next_line.c \
	  ft_printf.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_swap.c\
	  ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_matrix_free.c ft_matrix_dup.c
OBJS	= $(SRCS:.c=.o)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -rf libft.a

re: fclean
	$(MAKE) all
