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

	if (argc != 2)
		show_usage("./fdf <filename.fdf>");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		show_usage("./fdf <filename.fdf>");
	if (ft_strstr(argv[1], ".fdf") == NULL)
		show_usage("./fdf <filename.fdf>");
	return (fd);
}

int		key_hook(int keycode,void *param)
{
	t_conf	*conf = ((t_conf *)param);

	if (keycode == ESC)
		exit(0);
	if (keycode == I)
	{
		conf->state = conf->state == ISO ? FLAT : ISO;
		mlx_clear_window(conf->conn, conf->win);
		draw_map(*conf, conf->state);
	}
//	if (keycode == UP)
//	{
//		int y = 0;
//		while (y < conf->map_height) {
//			int x = 0;
//			while (x < conf->map_width)
//				conf->map_orig[y][x].coor.z = conf->map_orig[y][x++].coor.z * 2;
//			y++;
//		}
//		conf->map_iso = copy_map(*conf);
//	}
	fprintf(stderr, "%i", keycode);
	return (0);
}

int		main(int argc, char **argv)
{
	int 	fd;
	t_conf	conf;

	fd = open_file(argc, argv);
	conf = init_conf(fd);
	draw_map(conf, conf.state);
	mlx_key_hook(conf.win, key_hook, &conf);
	mlx_hook(conf.win, RED_CROSS, INT_MIN, go_close, NULL);
	mlx_loop(conf.conn);
	close(fd);
}
