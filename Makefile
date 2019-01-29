# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 17:35:37 by vlytvyne          #+#    #+#              #
#    Updated: 2019/01/28 19:24:06 by vlytvyne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc *.c -lmlx libft.a -framework OpenGL -framework AppKit -I includes

clean:

fclean: clean
	rm -rf a.out

re: fclean all

