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

#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"

int 	open_file(int argc, char **argv)
{
	int		fd;

	if (argc < 2)
		show_usage("./fdf <filename.fdf> [-height window height] [-width window width]");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		show_usage("./fdf <filename.fdf> [-height window height] [-width window width]");
	if (ft_strstr(argv[1], ".fdf") == NULL)
		show_usage("./fdf <filename.fdf> [-height window height] [-width window width]");
	return (fd);
}

void	move_up(t_point **map, int x, int y)
{
	map[y][x].coor.y -= 30;
}
void	move_down(t_point **map, int x, int y)
{
	map[y][x].coor.y += 30;
}
void	move_left(t_point **map, int x, int y)
{
	map[y][x].coor.x -= 30;
}
void	move_right(t_point **map, int x, int y)
{
	map[y][x].coor.x += 30;
}

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

void	map_iterator(t_conf conf, t_point **map, void (*func) (t_point **, int, int))
{
	int y;
	int x;

	y = 0;
	while (y < conf.map_height) {
		x = 0;
		while (x < conf.map_width) {
			func(map, x, y);
			x++;
		}
		y++;
	}
}

int		key_hook(int keycode,void *param)
{
	t_conf	*conf = ((t_conf *)param);
	t_point **map;

	if (keycode == ESC)
		exit(0);
	if (keycode == I)
		conf->state = conf->state == ISO ? FLAT : ISO;
	if (keycode == UP && conf->state == ISO)
		map_iterator(*conf, conf->map_iso, add_altitude);
	if (keycode == DOWN && conf->state)
		map_iterator(*conf, conf->map_iso, reduce_altitude);
	if (keycode >= ARROW_LEFT && keycode <= ARROW_UP)
	{
		unset_paddings(*conf, conf->state);
		t_coor *padd = conf->state == ISO ? &(conf->padding_iso) : &(conf->padding_flat);
		if (keycode == ARROW_UP)
			padd->y -= 20;
		else if (keycode == ARROW_DOWN)
			padd->y += 20;
		else if (keycode == ARROW_LEFT)
			padd->x -= 20;
		else if (keycode == ARROW_RIGHT)
			padd->x += 20;
		set_paddings(*conf, conf->state);
	}
	if (keycode == PLUS)
	{
		conf->line_len += 40;
		set_lines_len(*conf, conf->line_len, conf->state);
		if (conf->state == ISO)
			rotate_iso(*conf);
		set_paddings(*conf, conf->state);
	}
	if (keycode == MINUS && conf->line_len > 43)
	{
		conf->line_len -= 40;
		set_lines_len(*conf, conf->line_len, conf->state);
		if (conf->state == ISO)
			rotate_iso(*conf);
		set_paddings(*conf, conf->state);
	}
	mlx_clear_window(conf->conn, conf->win);
	draw_map(*conf, conf->state);
	return (0);
}


int		main(int argc, char **argv)
{
	int 	fd;
	t_conf	conf;

	fd = open_file(argc, argv);
	conf = init_conf(fd, argc, argv);
	draw_map(conf, conf.state);
	mlx_key_hook(conf.win, key_hook, &conf);
	mlx_hook(conf.win, RED_CROSS, INT_MIN, go_close, NULL);
	mlx_loop(conf.conn);
	close(fd);
}
