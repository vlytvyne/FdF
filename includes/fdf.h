/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:29:26 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/30 18:29:28 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_FDF
# define H_FDF

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
#  include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH 2560
# define SCREEN_HEIGHT 1395

# define ESC 53
# define RED_CROSS 17

typedef struct	s_point
{
	t_coor		coor;
	int 		color;
}				t_point;

typedef	struct	s_conf
{
	void	*conn;
	void	*win;
	int 	map_height;
	int 	map_width;
	t_point	**map;
}				t_conf;


void		draw_line(t_point p1, t_point p2, t_conf conf);
t_conf		init_conf(int fd);
void		del(void *pointer, size_t size);
void		draw_map(t_conf conf);

#endif
