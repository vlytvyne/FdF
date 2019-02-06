/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 19:32:03 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/02/05 19:32:06 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_altitude(t_point **map, int x, int y)
{
	if (map[y][x].coor.z > 0)
		map[y][x].coor.y -= 20;
	else if (map[y][x].coor.z < 0)
		map[y][x].coor.y += 20;
}

void	reduce_altitude(t_point **map, int x, int y)
{
	if (map[y][x].coor.z > 0)
		map[y][x].coor.y += 20;
	else if (map[y][x].coor.z < 0)
		map[y][x].coor.y -= 20;
}

void	map_iterator(t_conf conf, t_point **map,
		void (*func) (t_point **, int, int))
{
	int y;
	int x;

	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			func(map, x, y);
			x++;
		}
		y++;
	}
}
