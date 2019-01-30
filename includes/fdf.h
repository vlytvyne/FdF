/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:29:26 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/30 18:29:28 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_FDF
# define H_FDF

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
#  include <stdio.h>
# include <math.h>

typedef struct	s_point
{
	t_coor		coor;
	int 		color;
}				t_point;

void		draw_line(t_coor p1, t_coor p2, int color);

#  ifdef MAIN
void	*g_conn;
void	*g_win;
#  else
extern void	*g_conn;
extern void	*g_win;
#  endif

#endif
