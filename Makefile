# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 12:45:57 by mateferr          #+#    #+#              #
#    Updated: 2025/06/23 17:44:11 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus

SRC = src/free_exits.c src/utils.c pipex.c
BSRC = bonus/src/free_exits.c bonus/src/utils.c bonus/pipex.c \
bonus/src/multi_pipe.c bonus/src/get_next_line_px.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -o $(NAME)

bonus: $(BONUS)
	
$(BONUS): $(BOBJ)
	$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(BOBJ) -Llibft -lft -o $(BONUS)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) $(BONUS)

re: fclean all
