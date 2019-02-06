# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlytvyne <vlytvyne@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 17:01:53 by vlytvyne          #+#    #+#              #
#    Updated: 2019/02/06 17:01:53 by vlytvyne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCDIR = includes/

SRC = draw_line.c draw_map.c init_config.c iterator.c key_hook.c main.c paddings.c utils.c 

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

LIB = libft/libft.a

MLX = minilibx_macos/libmlx.a

INCDIR = includes

FLAGS = -Wall -Werror -Wextra

FRAMEWORKS = -framework OpenGL -framework AppKit

.PHONY: all clean fclean re cleanlib fcleanlib relib

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	gcc $(FLAGS) $(OBJ) $(LIB) $(MLX) $(FRAMEWORKS) -o $(NAME)

$(MLX):
	make -C minilibx_macos all

$(LIB):
	make -C libft all
	
$(OBJDIR)/%.o: ./%.c $(INCDIR)/*.h | $(OBJDIR)
	gcc $(FLAGS) -o $@ -c $< -I $(INCDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

cleanlib:
	make -C libft clean

fcleanlib:
	make -C libft fclean

relib:
	make -C libft re

cleanmlx:
	make -C minilibx_macos clean

fcleanmlx:
	make -C minilibx_macos clean

remlx:
	make -C minilibx_macos re

