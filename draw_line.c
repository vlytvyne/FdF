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

static void	draw_horizontal(t_point p1, t_point p2, int lenX, int lenY, int color, t_conf conf)
{
	int		x;
	int		i;
	double	y;
	double	increment;

	i = 0;
	if (lenX == 0)
		increment = 0;
	else
		increment = (double)lenY / lenX;
	x = fmin(p1.coor.x, p2.coor.x);
	y = x == p1.coor.x ? p1.coor.y : p2.coor.y;
	if (y == p1.coor.y && y > p2.coor.y)
		increment = -increment;
	else if (y == p2.coor.y && y > p1.coor.y)
		increment = -increment;
	while (i <= lenX)
	{
		mlx_pixel_put(conf.conn, conf.win, x, round(y), color);
		x++;
		y += increment;
		i++;
	}
}

static void	draw_vertical(t_point p1, t_point p2, int lenX, int lenY, int color, t_conf conf)
{
	int		y;
	int		i;
	double	x;
	double	increment;

	i = 0;
	if (lenY == 0)
		increment = 0;
	else
		increment = (double)lenX / lenY;
	y = fmin(p1.coor.y, p2.coor.y);
	x = y == p1.coor.y ? p1.coor.x : p2.coor.x;
	if (x == p1.coor.x && x > p2.coor.x)
		increment = -increment;
	else if (x == p2.coor.x && x > p1.coor.x)
		increment = -increment;
	while (i <= lenY)
	{
		mlx_pixel_put(conf.conn, conf.win, round(x), y, color);
		y++;
		x += increment;
		i++;
	}
}


//check if coordinates negative
void		draw_line(t_point p1, t_point p2, int color, t_conf conf)
{
	int		lenX;
	int		lenY;

	if (p1.coor.x < 0 || p1.coor.y < 0 || p2.coor.x < 0 || p2.coor.y < 0)
		error_exit("negative coordinates");
	lenX = abs(p1.coor.x - p2.coor.x);
	lenY = abs(p1.coor.y - p2.coor.y);
	if (lenX > lenY)
		draw_horizontal(p1, p2, lenX, lenY, color, conf);
	else
		draw_vertical(p1, p2, lenX, lenY, color, conf);
}
