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

static int	open_file(int argc, char **argv)
{
	int		fd;

	if (argc < 2)
		show_usage("./fdf <filename.fdf> [-height window height]"
" [-width window width]");
	fd = open(argv[1], O_RDONLY);
	if (ft_strequ(argv[1], "-help"))
		show_usage("./fdf <filename.fdf> [-height window height]"
" [-width window width] [-help]\n\n"
"IN PROGRAM CONTROLS:\n"
"\t[+] - zoom in.\n"
"\t[-] - zoom out.\n"
"\t[PageUp] - add altitude.\n"
"\t[PageDown] - reduce altitude.\n"
"\t[Arrows] - move the map.\n");
	if (fd == -1)
		show_usage("./fdf <filename.fdf> [-height window height]"
" [-width window width]");
	if (ft_strstr(argv[1], ".fdf") == NULL)
		show_usage("./fdf <filename.fdf> [-height window height]"
" [-width window width]");
	return (fd);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_conf	conf;

	fd = open_file(argc, argv);
	conf = init_conf(fd, argc, argv);
	draw_map(conf, conf.state);
	mlx_key_hook(conf.win, key_hook, &conf);
	mlx_hook(conf.win, RED_CROSS, INT_MIN, go_close, NULL);
	mlx_loop(conf.conn);
	close(fd);
}
