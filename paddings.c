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

void	define_len_padding_flat(t_conf *conf)
{
	int		max_horizontal;
	int		max_vertical;

	max_horizontal = conf->map_width - 1 != 0 ?
			conf->win_w / (conf->map_width - 1) : 50;
	max_vertical = conf->map_height - 1 != 0 ?
			conf->win_h / (conf->map_height - 1) : 50;
	if (max_horizontal > max_vertical)
	{
		conf->line_len = max_vertical > 2 ?
				max_vertical - 1 : max_vertical;
		conf->padding_flat.x = (conf->win_w -
				(conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (conf->win_h -
				(conf->line_len * (conf->map_height - 1))) / 2;
	}
	else
	{
		conf->line_len = max_horizontal > 2 ?
				max_horizontal - 1 : max_horizontal;
		conf->padding_flat.x = (conf->win_w -
				(conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (conf->win_h -
				(conf->line_len * (conf->map_height - 1))) / 2;
	}
}

void	define_padding_iso(t_conf *conf)
{
	int		first_vertex;
	int		second_vertex;
	int		distance;
	int		padding;

	first_vertex = conf->map_iso[conf->map_height - 1][0].coor.x;
	second_vertex = conf->map_iso[0][conf->map_width - 1].coor.x;
	distance = second_vertex - first_vertex;
	padding = (conf->win_w - distance) / 2;
	conf->padding_iso.x = padding - first_vertex;
	first_vertex = conf->map_iso[0][0].coor.y;
	second_vertex = conf->map_iso[conf->map_height - 1]
			[conf->map_width - 1].coor.y;
	distance = second_vertex - first_vertex;
	padding = (conf->win_h - distance) / 2;
	conf->padding_iso.y = padding - first_vertex;
}

void	unset_paddings(t_conf conf, int state)
{
	int		y;
	int		x;
	t_point	**map;
	t_coor	padd;

	padd = conf.state == ISO ? conf.padding_iso : conf.padding_flat;
	map = conf.state == ISO ? conf.map_iso : conf.map_flat;
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			map[y][x].coor.x -= padd.x;
			map[y][x].coor.y -= padd.y;
			x++;
		}
		y++;
	}
}

void	set_paddings(t_conf conf, int state)
{
	int		y;
	int		x;
	t_point	**map;
	t_coor	padd;

	padd = state == ISO ? conf.padding_iso : conf.padding_flat;
	map = state == ISO ? conf.map_iso : conf.map_flat;
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			map[y][x].coor.x += padd.x;
			map[y][x].coor.y += padd.y;
			x++;
		}
		y++;
	}
}
