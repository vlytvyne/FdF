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

int		main(int argc, char **argv)
{
	int 	fd;
	t_conf	conf;

	fd = open_file(argc, argv);
	conf = init_conf(fd);

//	for(int y = 0; y < conf.map_height; y++)
//	{
//		for(int x = 0; x < conf.map_width; x++)
//			fprintf(stderr, "%i ", conf.map[y][x].coor.z);
//		fprintf(stderr, "\n");
//	}
//	t_point p1;
//	p1.coor.x = 0;
//	p1.coor.y = 0;
//	t_point p2;
//	p2.coor.x = 50;
//	p2.coor.y = 50;
//	draw_line(p1, p2, 0xFF0000, conf);

	draw_map(conf);

//	for(int i = 0; i < conf.map_height; i++)
//	{
//		for(int j = 0; j < conf.map_width; j++)
//			fprintf(stderr, "%i ", conf.map[i][j].coor.y);
//		fprintf(stderr, "\n");
//	}

	mlx_loop(conf.conn);
	close(fd);
}
