# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 15:37:03 by msuarez-          #+#    #+#              #
#    Updated: 2020/06/02 14:11:32 by msuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = testing.c getinfo.c map.c key.c image.c draw.c

OBJECTS = $(subst .c,.o,$(SRC))

LIBFT = libft/libft.a

.PHONY = all clean fclean clean re

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
		@make -C libft/
		@cc $(FLAGS) -I/usr/local/include $(SRC) $(LIBFT) \
		-L/usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
		@make clean -C libft/
		@/bin/rm -f $(OBJECTS)

fclean: clean
		@/bin/rm -f $(LIBFT)
		@/bin/rm -f $(NAME)

re: fclean all
