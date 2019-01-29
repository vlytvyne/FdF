/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:43:18 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/29 16:38:23 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
# include <stdio.h>
#include <math.h>

void	*g_conn;
void	*g_win;

void draw_horizontal(t_coor p1, t_coor p2, int lenX, int lenY)
{
	int		x;
	int		i;
	double	y;
	double	increment;

	i = 0;
	increment = (double)lenY / lenX;
	x = p1.x < p2.x ? p1.x : p2.x;
	y = x == p1.x ? p1.y : p2.y;
	if (y == p1.y && y > p2.y)
		increment = -increment;
	else if (y == p2.y && y > p1.y)
		increment = -increment;
	while (i <= lenX)
	{
		mlx_pixel_put(g_conn, g_win, x, (int)y, 0xFF0000);
		x++;
		y += increment;
		i++;
	}
}

void	draw_vertical(t_coor p1, t_coor p2, int lenX, int lenY)
{
	int		y;
	int		i;
	double	x;
	double	increment;

	i = 0;
	increment = (double)lenX / lenY;
	y = p1.y < p2.y ? p1.y : p2.y;
	x = y == p1.y ? p1.x : p2.x;
	if (x == p1.x && x > p2.x)
		increment = -increment;
	else if (x == p2.x && x > p1.x)
		increment = -increment;
	while (i <= lenY)
	{
		mlx_pixel_put(g_conn, g_win, (int)x, y, 0xFF0000);
		y++;
		x += increment;
		i++;
	}
}


//check if coordinates negative
void	draw_line(t_coor p1, t_coor p2)
{
	int		lenX;
	int		lenY;

	if (p1.x < 0 || p1.y < 0 || p2.x < 0 || p2.y < 0)
		return;
	lenX = fabs(p1.x - p2.x);
	lenY = fabs(p1.y - p2.y);
	if (lenX > lenY)
		draw_horizontal(p1, p2, lenX, lenY);
	else
		draw_vertical(p1, p2, lenX, lenY);
}

int		main(void)
{
	t_coor p1 = {0, 0};
	t_coor p2 = {100, 50};

	g_conn = mlx_init();
	g_win = mlx_new_window(g_conn, 1000, 800, "FDF");
	draw_line(p1, p2);
	mlx_loop(g_conn);
}