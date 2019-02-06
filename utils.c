/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:01:24 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/31 18:01:25 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		go_close(void *param)
{
	param = NULL;
	exit(0);
}

t_point	**copy_map(t_conf conf)
{
	t_point	**map_copy;
	int		y;

	map_copy = (t_point**)malloc(sizeof(t_point*) * conf.map_height);
	ft_memcpy(map_copy, conf.map_orig, sizeof(t_point*) * conf.map_height);
	y = 0;
	while (y < conf.map_height)
	{
		map_copy[y] = (t_point*)malloc(sizeof(t_list) * conf.map_width);
		ft_memcpy(map_copy[y], conf.map_orig[y],
				sizeof(t_list) * conf.map_width);
		y++;
	}
	return (map_copy);
}

void	set_lines_len(t_conf conf, int len, int state)
{
	int		y;
	int		x;
	t_point	**map;

	if (state == ISO)
		map = conf.map_iso;
	else
		map = conf.map_flat;
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			map[y][x].coor.x = conf.map_orig[y][x].coor.x * len;
			map[y][x].coor.y = conf.map_orig[y][x].coor.y * len;
			map[y][x].coor.z = conf.map_orig[y][x].coor.z * len / 10;
			x++;
		}
		y++;
	}
}

void	set_window_size(t_conf *conf, int argc, char **argv)
{
	int i;

	i = 2;
	conf->win_h = SCREEN_HEIGHT_MAX;
	conf->win_w = SCREEN_WIDTH_MAX;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-height") && i + 1 < argc)
			conf->win_h = ft_atoi(argv[++i]);
		if (ft_strequ(argv[i], "-width") && i + 1 < argc)
			conf->win_w = ft_atoi(argv[++i]);
		if (ft_strequ(argv[i], "-help"))
			show_usage("./fdf <filename.fdf> [-height window height]"
" [-width window width] [-help]\n\nIN PROGRAM CONTROLS:\n"
"\t[+] - zoom in.\n"
"\t[-] - zoom out.\n"
"\t[PageUp] - add altitude.\n"
"\t[PageDown] - reduce altitude.\n"
"\t[Arrows] - move the map.\n");
		i++;
	}
	if (conf->win_h < 1 || conf->win_h > SCREEN_HEIGHT_MAX)
		conf->win_h = SCREEN_HEIGHT_MAX;
	if (conf->win_w < 1 || conf->win_w > SCREEN_WIDTH_MAX)
		conf->win_w = SCREEN_WIDTH_MAX;
}

void	rotate_iso(t_conf conf)
{
	int		y;
	int		x;
	int		prev_x;
	int		prev_y;

	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			prev_x = conf.map_iso[y][x].coor.x;
			prev_y = conf.map_iso[y][x].coor.y;
			conf.map_iso[y][x].coor.x = (prev_x - prev_y) * cos(0.523599);
			conf.map_iso[y][x].coor.y = (prev_x + prev_y) * sin(0.523599)
					- conf.map_iso[y][x].coor.z;
			x++;
		}
		y++;
	}
}
