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

static void	draw_horizontal(t_coor p1, t_coor p2, int lenX, int lenY, int color, t_conf conf)
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
	x = p1.x < p2.x ? p1.x : p2.x;
	y = x == p1.x ? p1.y : p2.y;
	if (y == p1.y && y > p2.y)
		increment = -increment;
	else if (y == p2.y && y > p1.y)
		increment = -increment;
	while (i <= lenX)
	{
		mlx_pixel_put(conf.conn, conf.win, x, round(y), color);
		x++;
		y += increment;
		i++;
	}
}

static void	draw_vertical(t_coor p1, t_coor p2, int lenX, int lenY, int color, t_conf conf)
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
	y = p1.y < p2.y ? p1.y : p2.y;
	x = y == p1.y ? p1.x : p2.x;
	if (x == p1.x && x > p2.x)
		increment = -increment;
	else if (x == p2.x && x > p1.x)
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
void		draw_line(t_coor p1, t_coor p2, int color, t_conf conf)
{
	int		lenX;
	int		lenY;

	if (p1.x < 0 || p1.y < 0 || p2.x < 0 || p2.y < 0)
		error_exit("negative coordinates");
	lenX = abs(p1.x - p2.x);
	lenY = abs(p1.y - p2.y);
	if (lenX > lenY)
		draw_horizontal(p1, p2, lenX, lenY, color, conf);
	else
		draw_vertical(p1, p2, lenX, lenY, color, conf);
}
