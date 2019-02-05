/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paddings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:28:25 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/02/05 16:28:26 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	define_len_padding_flat(t_conf *conf)
{
	int 	max_horizontal;
	int 	max_vertical;

	max_horizontal = conf->map_width - 1 != 0 ? SCREEN_WIDTH / (conf->map_width - 1) : 50;
	max_vertical = conf->map_height - 1 != 0 ? SCREEN_HEIGHT / (conf->map_height - 1) : 50;
	if (max_horizontal > max_vertical)
	{
		conf->line_len = max_vertical > 2 ? max_vertical - 1 : max_vertical;
		conf->padding_flat.x = (SCREEN_WIDTH - (conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (SCREEN_HEIGHT - (conf->line_len * (conf->map_height - 1))) / 2;
	}
	else
	{
		conf->line_len = max_horizontal > 2 ? max_horizontal - 1 : max_horizontal;
		conf->padding_flat.x = (SCREEN_WIDTH - (conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (SCREEN_HEIGHT - (conf->line_len * (conf->map_height - 1))) / 2;
	}
}

void	define_padding_iso(t_conf *conf)
{
	int		first_vertex;
	int 	second_vertex;
	int 	distance;
	int 	padding;

	first_vertex = conf->map_iso[conf->map_height - 1][0].coor.x;
	second_vertex = conf->map_iso[0][conf->map_width - 1].coor.x;
	distance = second_vertex - first_vertex;
	padding = (SCREEN_WIDTH - distance) / 2;
	conf->padding_iso.x = padding - first_vertex;
	first_vertex = conf->map_iso[0][0].coor.y;
	second_vertex = conf->map_iso[conf->map_height - 1][conf->map_width - 1].coor.y;
	distance = second_vertex - first_vertex;
	padding = (SCREEN_HEIGHT - distance) / 2;
	conf->padding_iso.y = padding - first_vertex;
}

void	set_paddings(t_conf conf)
{
	int 	y;
	int 	x;
	t_point	**map;


	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			conf.map_flat[y][x].coor.x += conf.padding_flat.x;
			conf.map_flat[y][x].coor.y += conf.padding_flat.y;
			conf.map_iso[y][x].coor.x += conf.padding_iso.x;
			conf.map_iso[y][x].coor.y += conf.padding_iso.y;
			x++;
		}
		y++;
	}
}
