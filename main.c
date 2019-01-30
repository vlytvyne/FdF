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

t_list	*get_lines(int fd, int *lines_count) {
	char	*s;
	t_list	*list;
	t_list	*head;

	*lines_count = 0;
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
		(*lines_count)++;
	}
	return (head);
}

t_point	**extract_map(t_list *lines, int lines_count)
{

}

int		main(int argc, char **argv)
{
	int 	fd;
	int 	lines_count;
	t_list	*lines;

	if (argc != 2)
		show_usage("./fdf <filename.fdf>");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		show_usage("./fdf <filename.fdf>");
	if (ft_strstr(argv[1], ".fdf") == NULL)
		show_usage("./fdf <filename.fdf>");
	if ((lines = get_lines(fd, &lines_count)) == NULL)
		error_exit("the map is empty");


	g_conn = mlx_init();
	g_win = mlx_new_window(g_conn, 1000, 800, "FDF");

	mlx_loop(g_conn);
	close(fd);
}