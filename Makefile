# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 12:45:57 by mateferr          #+#    #+#              #
#    Updated: 2025/06/26 13:49:16 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = src/free_exits.c src/utils.c src/get_next_line_px.c src/here_doc.c \
src/multi_pipe.c src/arg_formater.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(OBJ) pipex.c -Llibft -lft -o $(NAME)

test: $(OBJ)
	$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(OBJ) tests.c -Llibft -lft

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all
