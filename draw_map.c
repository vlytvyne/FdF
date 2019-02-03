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

void	draw_map(t_conf conf)
{
	int 	y;
	int 	x;
	t_point	**map;

	if (conf.state == ISO)
		map = conf.map_iso;
	else
		map = conf.map_flat;
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			if (x + 1 < conf.map_width)
				draw_line(map[y][x], map[y][x + 1], conf);
			if (y + 1 < conf.map_height)
				draw_line(map[y][x], map[y + 1][x], conf);
			x++;
		}
		y++;
	}
}
