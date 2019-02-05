/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:59:22 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/31 17:59:24 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*get_lines(int fd, int *map_height)
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

static t_point	init_point(int x, int y, char *z_token)
{
	t_point	p;
	char 	*color;

	p.coor.x = x;
	p.coor.y = y;
	p.coor.z = ft_atoi(z_token);
	p.color = (color = ft_strchr(z_token, ',')) ? atoi_hex(color + 1) : 0xFFFFFF;
	return (p);
}

static t_point	**extract_map(t_list *lines, t_conf conf)
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

static int 	count_map_width(t_list *lines)
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

void	set_window_size(t_conf *conf, int argc, char **argv)
{
	int i = 2;
	conf->window_height = SCREEN_HEIGHT_MAX;
	conf->window_width = SCREEN_WIDTH_MAX;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-height") && i + 1 < argc)
			conf->window_height = ft_atoi(argv[++i]);
		if (ft_strequ(argv[i], "-width") && i + 1 < argc)
			conf->window_width = ft_atoi(argv[++i]);
		i++;
	}
	if (conf->window_height < 1 || conf->window_height > SCREEN_HEIGHT_MAX)
		conf->window_height = SCREEN_HEIGHT_MAX;
	if (conf->window_width < 1 || conf->window_width > SCREEN_WIDTH_MAX)
		conf->window_width = SCREEN_WIDTH_MAX;
}

t_conf	init_conf(int fd, int argc, char **argv)
{
	t_conf	conf;
	t_list	*lines;
	t_point	**map;

	set_window_size(&conf, argc, argv);
	conf.conn = mlx_init();
	conf.win = mlx_new_window(conf.conn, conf.window_width, conf.window_height, "FDF");
	lines = get_lines(fd, &conf.map_height);
	conf.map_width = count_map_width(lines);
	if (conf.map_height == 1 && conf.map_width == 1)
		error_exit("One point is not enough to build a map.");
	if (conf.map_height == 1 || conf.map_width == 1)
		error_exit("One line is not enough to build a map.");
	conf.map_orig = extract_map(lines, conf);
	conf.map_flat = copy_map(conf);
	conf.map_iso = copy_map(conf);
	define_len_padding_flat(&conf);
	set_lines_len(conf, conf.line_len, FLAT);
	set_lines_len(conf, conf.line_len, ISO);
	rotate_iso(conf);
	define_padding_iso(&conf);
	set_paddings(conf);
	conf.state = FLAT;
	lstdel_std(lines);
	return (conf);
}
