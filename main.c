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
	if (keycode == ESC)
		exit(0);
	if (keycode == 17)
		exit(0);
	fprintf(stderr, "%i", keycode);
	return (0);
}

int 	go_close(void *param)
{
	exit(0);
}

int		main(int argc, char **argv)
{
	int 	fd;
	t_conf	conf;

	fd = open_file(argc, argv);
	conf = init_conf(fd);


	draw_map(conf);
//	t_point p1;
//	p1.coor.x = 0;
//	p1.coor.y = SCREEN_HEIGHT - 100;
//	p1.color = 0xFF0000;
//	t_point p2;
//	p2.coor.x = SCREEN_WIDTH;
//	p2.coor.y = SCREEN_HEIGHT - 100;
//	p2.color = 0xFFFFFF;
//	draw_line(p2, p1, conf);

//	for(int i = 0; i < conf.map_height; i++)
//	{
//		for(int j = 0; j < conf.map_width; j++)
//			fprintf(stderr, "%i ", conf.map[i][j].coor.y);
//		fprintf(stderr, "\n");
//	}

	mlx_key_hook(conf.win, key_hook, NULL);
	mlx_hook(conf.win, RED_CROSS, INT_MIN, go_close, NULL);
	mlx_loop(conf.conn);
	close(fd);
}
