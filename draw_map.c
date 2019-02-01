/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:01:24 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/31 18:01:25 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//TODO: ISO
//TODO: ALTITUDE

void	set_lines_len(t_conf conf, int len)
{
	int 	y;
	int 	x;

	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			conf.map[y][x].coor.x *= len;
			conf.map[y][x].coor.y *= len;
			x++;
		}
		y++;
	}
}

void	iso(t_conf conf)
{
	int 	y;
	int 	x;
	int 	prev_x;
	int 	prev_y;

	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			prev_x = conf.map[y][x].coor.x;
			prev_y = conf.map[y][x].coor.y;
			conf.map[y][x].coor.x = (prev_x - prev_y) * cos(0.523599) + 500;
			conf.map[y][x].coor.y = -conf.map[y][x].coor.z + (prev_x + prev_y) * sin(0.523599);
			x++;
		}
		y++;
	}
}

void	draw_map(t_conf conf)
{
	int 	y;
	int 	x;

	set_lines_len(conf, 30);
	iso(conf);
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			if (x + 1 < conf.map_width)
				draw_line(conf.map[y][x], conf.map[y][x + 1], conf);
			if (y + 1 < conf.map_height)
				draw_line(conf.map[y][x], conf.map[y + 1][x], conf);
			x++;
		}
		y++;
	}

//	for(int i = 0; i < conf.map_height; i++)
//	{
//		for(int j = 0; j < conf.map_width; j++)
//			fprintf(stderr, "%i ", conf.map[i][j].coor.y);
//		fprintf(stderr, "\n");
//	}
}
