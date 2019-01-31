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

t_list	*get_lines(int fd, int *map_height)
{
	char	*s;
	t_list	*list;
	t_list	*head;

	*map_height = 0;
	head = NULL;
	while (get_next_line(fd, &s)) {
		if (head == NULL)
		{
			head = malloc(sizeof(t_list));
			head->content = s;
			head->next = NULL;
		}
		else
		{
			list = malloc(sizeof(t_list));
			list->content = s;
			list->next = NULL;
			lst_add_end(head, list);
		}
		(*map_height)++;
	}
	if (head == NULL)
		error_exit("the map is empty");
	return (head);
}

t_point	init_point(int x, int y, char *z_token)
{
	t_point	p;
	char 	*color;

	p.coor.x = x;
	p.coor.y = y;
	p.coor.z = ft_atoi(z_token);
	p.color = (color = ft_strchr(z_token, ',')) ? atoi_hex(color + 1) : 0;
	return (p);
}

t_point	**extract_map(t_list *lines, t_conf conf)
{
	t_point	**map;
	char	**tokens_z;
	int 	y;
	int 	x;

	map = (t_point**)malloc(sizeof(t_point*) * conf.map_height);
	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		map[y] = (t_point*)malloc(sizeof(t_list) * conf.map_width);
		tokens_z = ft_strsplit((char*)lines->content, ' ');
		while (x < conf.map_width)
		{
			map[y][x] = init_point(x, y, tokens_z[x]);
			free(tokens_z[x]);
			x++;
		}
		y++;
		free(tokens_z);
		lines = lines->next;
	}
	return (map);
}

int 	count_map_width(t_list *lines)
{
	int		map_width;
	map_width = count_words((char*)lines->content, ' ');
	while (lines)
	{
		if (map_width != count_words((char*)lines->content, ' '))
			error_exit("lines has different length");
		lines = lines->next;
	}
	return (map_width);
}

void	del(void *pointer, size_t size)
{
	free(pointer);
}

t_conf	init_conf(int fd)
{
	t_conf	conf;
	t_list	*lines;
	t_point	**map;

	conf.conn = mlx_init();
	conf.win = mlx_new_window(conf.conn, 1000, 800, "FDF");
	lines = get_lines(fd, &conf.map_height);
	conf.map_width = count_map_width(lines);
	conf.map = extract_map(lines, conf);
	ft_lstdel(&lines, del);
	return (conf);
}

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

	for(int y = 0; y < conf.map_height; y++)
	{
		for(int x = 0; x < conf.map_width; x++)
			fprintf(stderr, "%i ", conf.map[y][x].coor.z);
		fprintf(stderr, "\n");
	}
	mlx_loop(conf.conn);
	close(fd);
}
