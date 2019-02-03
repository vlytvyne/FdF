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

int 	define_line_len(t_conf conf)
{
	int 	len;
	int 	max_horizontal;
	int 	max_vertical;

	max_horizontal = (SCREEN_WIDTH * 0.9) / (conf.map_width - 1);
	max_vertical = (SCREEN_HEIGHT * 0.9) / (conf.map_height - 1);
	len = max_horizontal > max_vertical ? max_vertical : max_horizontal;
	return (len);
}

t_conf	init_conf(int fd)
{
	t_conf	conf;
	t_list	*lines;
	t_point	**map;

	conf.conn = mlx_init();
	conf.win = mlx_new_window(conf.conn, SCREEN_WIDTH, SCREEN_HEIGHT, "FDF");
	lines = get_lines(fd, &conf.map_height);
	conf.map_width = count_map_width(lines);
	conf.map_orig = extract_map(lines, conf);
	conf.map_flat = copy_map(conf);
	conf.map_iso = copy_map(conf);
	conf.line_len_flat = define_line_len(conf);
	set_lines_len(conf, conf.line_len_flat, FLAT);
	set_lines_len(conf, 50, ISO);
	rotate_iso(conf, 30);
	conf.state = FLAT;
	lstdel_std(lines);
	return (conf);
}
