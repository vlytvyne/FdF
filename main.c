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

#define MAIN
#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"



int		main(int argc, char **argv)
{
	if (argc != 2)
		show_usage("./fdf <filename.fdf>");
	int fd = open(argv[1], O_RDONLY);
	t_coor p1 = {2, 2};
	t_coor p2 = {32, 3};

	g_conn = mlx_init();
	g_win = mlx_new_window(g_conn, 1000, 800, "FDF");
	draw_line(p1, p2, 0xFF0000);
	mlx_loop(g_conn);
	close(fd);
}