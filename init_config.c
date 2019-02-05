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
void 	define_len_padding_flat(t_conf *conf)
{
	int 	max_horizontal;
	int 	max_vertical;

	max_horizontal = conf->map_width - 1 != 0 ? SCREEN_WIDTH / (conf->map_width - 1) : 50;
	max_vertical = conf->map_height - 1 != 0 ? SCREEN_HEIGHT / (conf->map_height - 1) : 50;
	if (max_horizontal > max_vertical)
	{
		conf->line_len = max_vertical > 2 ? max_vertical - 1 : max_vertical;
		conf->padding_flat.x = (SCREEN_WIDTH - (conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (SCREEN_HEIGHT - (conf->line_len * (conf->map_height - 1))) / 2;
	}
	else
	{
		conf->line_len = max_horizontal > 2 ? max_horizontal - 1 : max_horizontal;
		conf->padding_flat.x = (SCREEN_WIDTH - (conf->line_len * (conf->map_width - 1))) / 2;
		conf->padding_flat.y = (SCREEN_HEIGHT - (conf->line_len * (conf->map_height - 1))) / 2;
	}
}

void	define_padding_iso(t_conf *conf)
{
	int		first_vertex;
	int 	second_vertex;
	int 	distance;
	int 	padding;

	first_vertex = conf->map_iso[conf->map_height - 1][0].coor.x;
	second_vertex = conf->map_iso[0][conf->map_width - 1].coor.x;
	distance = second_vertex - first_vertex;
	padding = (SCREEN_WIDTH - distance) / 2;
	conf->padding_iso.x = padding - first_vertex;
	first_vertex = conf->map_iso[0][0].coor.y;
	second_vertex = conf->map_iso[conf->map_height - 1][conf->map_width - 1].coor.y;
	distance = second_vertex - first_vertex;
	padding = (SCREEN_HEIGHT - distance) / 2;
	conf->padding_iso.y = padding - first_vertex;
}

void	set_paddings(t_conf conf)
{
	int 	y;
	int 	x;
	t_point	**map;


	y = 0;
	while (y < conf.map_height)
	{
		x = 0;
		while (x < conf.map_width)
		{
			conf.map_flat[y][x].coor.x += conf.padding_flat.x;
			conf.map_flat[y][x].coor.y += conf.padding_flat.y;
			conf.map_iso[y][x].coor.x += conf.padding_iso.x;
			conf.map_iso[y][x].coor.y += conf.padding_iso.y;
			x++;
		}
		y++;
	}
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
	if (conf.map_height == 1 && conf.map_width == 1)
		error_exit("One point is not enough to build a map.");
	conf.map_orig = extract_map(lines, conf);
	conf.map_flat = copy_map(conf);
	conf.map_iso = copy_map(conf);
	define_len_padding_flat(&conf);
	set_lines_len(conf, conf.line_len, FLAT);
	set_lines_len(conf, conf.line_len, ISO);
	rotate_iso(conf, 30);
	define_padding_iso(&conf);
	set_paddings(conf);
	conf.state = FLAT;
	lstdel_std(lines);
	return (conf);
}
