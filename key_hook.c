/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:45 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/02/06 16:50:30 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	refresh_map(t_conf *conf)
{
	set_lines_len(*conf, conf->line_len, conf->state);
	if (conf->state == ISO)
		rotate_iso(*conf);
	set_paddings(*conf, conf->state);
}

static void	move_map(int keycode, t_conf *conf)
{
	if (keycode == ARROW_UP)
		change_padding(conf, conf->state, 0, -100);
	else if (keycode == ARROW_DOWN)
		change_padding(conf, conf->state, 0, 100);
	else if (keycode == ARROW_LEFT)
		change_padding(conf, conf->state, -100, 0);
	else if (keycode == ARROW_RIGHT)
		change_padding(conf, conf->state, 100, 0);
}

static void	increase_size(t_conf *conf)
{
	conf->line_len += conf->line_len / 3 + 1;
	refresh_map(conf);
}

static void	decrease_size(t_conf *conf)
{
	conf->line_len -= conf->line_len / 3 + 1;
	refresh_map(conf);
}

int			key_hook(int keycode, void *param)
{
	t_conf	*conf;

	conf = ((t_conf *)param);
	if (keycode == ESC)
		exit(0);
	if (keycode == I)
	{
		conf->state = conf->state == ISO ? FLAT : ISO;
		refresh_map(conf);
	}
	if (keycode == UP && conf->state == ISO)
		map_iterator(*conf, conf->map_iso, add_altitude);
	if (keycode == DOWN && conf->state)
		map_iterator(*conf, conf->map_iso, reduce_altitude);
	if (keycode >= ARROW_LEFT && keycode <= ARROW_UP)
		move_map(keycode, conf);
	if (keycode == PLUS || keycode == PLUS_NUM)
		increase_size(conf);
	if ((keycode == MINUS || keycode == MINUS_NUM) && conf->line_len > 3)
		decrease_size(conf);
	mlx_clear_window(conf->conn, conf->win);
	draw_map(*conf, conf->state);
	return (0);
}
