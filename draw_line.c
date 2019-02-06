/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:27:51 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/30 18:27:54 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_rgb	get_gradient(t_point start, t_point end, int len)
{
	t_rgb	chanels_start;
	t_rgb	chanels_end;
	t_rgb	change;

	chanels_start.red = (start.color >> 16) & 0xFF;
	chanels_start.green = (start.color >> 8) & 0xFF;
	chanels_start.blue = start.color & 0xFF;
	chanels_end.red = (end.color >> 16) & 0xFF;
	chanels_end.green = (end.color >> 8) & 0xFF;
	chanels_end.blue = end.color & 0xFF;
	change.red = -((chanels_start.red - chanels_end.red) / len);
	change.green = -((chanels_start.green - chanels_end.green) / len);
	change.blue = -((chanels_start.blue - chanels_end.blue) / len);
	return (change);
}

static int		get_color(int start_color, t_rgb change, int pixel)
{
	int		color;

	color = 0;
	change.red *= pixel;
	change.green *= pixel;
	change.blue *= pixel;
	color = ((start_color >> 16) & 0xFF) + round(change.red);
	color = color << 8;
	color += ((start_color >> 8) & 0xFF) + round(change.green);
	color = color << 8;
	color += (start_color & 0xFF) + round(change.blue);
	if (color < 0)
		color = 0;
	return (color);
}

static void		draw_horizontal(t_point start, t_point end,
		t_coor distance, t_conf conf)
{
	int		x;
	int		i;
	double	y;
	double	increment;
	t_rgb	color_change;

	i = 0;
	if (distance.x == 0)
		increment = 0;
	else
		increment = (double)distance.y / distance.x;
	x = start.coor.x;
	y = start.coor.y;
	increment = y > end.coor.y ? -increment : increment;
	color_change = get_gradient(start, end, distance.x);
	while (i <= distance.x)
	{
		mlx_pixel_put(conf.conn, conf.win, x, round(y),
				get_color(start.color, color_change, i));
		x++;
		y += increment;
		i++;
	}
}

static void		draw_vertical(t_point start, t_point end,
		t_coor distance, t_conf conf)
{
	int		y;
	int		i;
	double	x;
	double	increment;
	t_rgb	color_change;

	i = 0;
	if (distance.y == 0)
		increment = 0;
	else
		increment = (double)distance.x / distance.y;
	y = start.coor.y;
	x = start.coor.x;
	increment = x > end.coor.x ? -increment : increment;
	color_change = get_gradient(start, end, distance.y);
	while (i <= distance.y)
	{
		mlx_pixel_put(conf.conn, conf.win, round(x), y,
				get_color(start.color, color_change, i));
		y++;
		x += increment;
		i++;
	}
}

void			draw_line(t_point p1, t_point p2, t_conf conf)
{
	t_coor	distance;

	distance.x = abs(p1.coor.x - p2.coor.x);
	distance.y = abs(p1.coor.y - p2.coor.y);
	if (distance.x > distance.y)
	{
		if (p1.coor.x < p2.coor.x)
			draw_horizontal(p1, p2, distance, conf);
		else
			draw_horizontal(p2, p1, distance, conf);
	}
	else
	{
		if (p1.coor.y < p2.coor.y)
			draw_vertical(p1, p2, distance, conf);
		else
			draw_vertical(p2, p1, distance, conf);
	}
}
