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

# define SCREEN_WIDTH_MAX 2560
# define SCREEN_HEIGHT_MAX 1395

# define ESC 53
# define I 34
# define UP 116
# define DOWN 121
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define PLUS 24
# define PLUS_NUM 69
# define MINUS 27
# define MINUS_NUM 78
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
	int 			win_h;
	int 			win_w;
}					t_conf;


void				draw_line(t_point p1, t_point p2, t_conf conf);
t_conf				init_conf(int fd, int argc, char **argv);
void				draw_map(t_conf conf, int state);
int 				go_close(void *param);
t_point				**copy_map(t_conf conf);
void				set_lines_len(t_conf conf, int len, int state);
void				rotate_iso(t_conf conf);
void 				define_len_padding_flat(t_conf *conf);
void				define_padding_iso(t_conf *conf);

void				change_padding(t_conf *conf, int state, int p_x, int p_y);
void				set_paddings(t_conf conf, int state);
void				set_window_size(t_conf *conf, int argc, char **argv);
void				add_altitude(t_point **map, int x, int y);
void				reduce_altitude(t_point **map, int x, int y);
void				map_iterator(t_conf conf, t_point **map,
					void (*func) (t_point **, int, int));
int					key_hook(int keycode, void *param);

#endif
