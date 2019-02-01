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

static void	draw_horizontal(t_point start, t_point end, int lenX, int lenY, t_conf conf)
{
	int		x;
	int		i;
	double	y;
	double	increment;
	double	color_change;

	i = 0;
	if (lenX == 0)
		increment = 0;
	else
		increment = (double)lenY / lenX;
	x = start.coor.x;
	y = start.coor.y;
	increment = y > end.coor.y ? -increment : increment;
	if (start.color > end.color)
		color_change = -(double)(start.color - end.color) / lenX;
	else
		color_change = (double)(end.color - start.color) / lenX;
	while (i <= lenX)
	{
		mlx_pixel_put(conf.conn, conf.win, x, round(y), round(start.color + (color_change * i)));
		x++;
		y += increment;
		i++;
	}
}

static void	draw_vertical(t_point start, t_point end, int lenX, int lenY, t_conf conf)
{
	int		y;
	int		i;
	double	x;
	double	increment;
	double	color_change;

	i = 0;
	if (lenY == 0)
		increment = 0;
	else
		increment = (double)lenX / lenY;
	y = start.coor.y;
	x = start.coor.x;
	increment = x > end.coor.x ? -increment : increment;
	if (start.color > end.color)
		color_change = -(double)(start.color - end.color) / lenY;
	else
		color_change = (double)(end.color - start.color) / lenY;
	while (i <= lenY)
	{
		mlx_pixel_put(conf.conn, conf.win, round(x), y, round(start.color + (color_change * i)));
		y++;
		x += increment;
		i++;
	}
}

void		draw_line(t_point p1, t_point p2, t_conf conf)
{
	int		lenX;
	int		lenY;

//	if (p1.coor.x < 0 || p1.coor.y < 0 || p2.coor.x < 0 || p2.coor.y < 0)
//		error_exit("negative coordinates");
	lenX = abs(p1.coor.x - p2.coor.x);
	lenY = abs(p1.coor.y - p2.coor.y);
	if (lenX > lenY)
	{
		if (p1.coor.x < p2.coor.x)
			draw_horizontal(p1, p2, lenX, lenY, conf);
		else
			draw_horizontal(p2, p1, lenX, lenY, conf);
	}
	else
	{
		if (p1.coor.y < p2.coor.y)
			draw_vertical(p1, p2, lenX, lenY, conf);
		else
			draw_vertical(p2, p1, lenX, lenY, conf);

	}
}
