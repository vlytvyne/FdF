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
# define I 34
# define UP 116
# define RED_CROSS 17

# define FLAT 0
# define ISO 1

typedef struct		s_point
{
	t_coor			coor;
	int 			color;
}					t_point;

typedef	struct		s_rgb
{
	double 			red;
	double 			green;
	double 			blue;
}					t_rgb;

typedef	struct		s_conf
{
	void			*conn;
	void			*win;
	int 			map_height;
	int 			map_width;
	t_point			**map_orig;
	t_point			**map_flat;
	t_point			**map_iso;
	int 			line_len;
	t_coor			padding_flat;
	t_coor			padding_iso;
	int 			state;
}					t_conf;


void		draw_line(t_point p1, t_point p2, t_conf conf);
t_conf		init_conf(int fd);
void		draw_map(t_conf conf, int state);
int 		go_close(void *param);
t_point		**copy_map(t_conf conf);
void		set_lines_len(t_conf conf, int len, int state);
void		rotate_iso(t_conf conf, double angle);

#endif
