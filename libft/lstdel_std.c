/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdel_std.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:52:00 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/02/01 12:58:03 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *pointer, size_t size)
{
	size = 0;
	free(pointer);
}

void		lstdel_std(t_list *list)
{
	ft_lstdel(&list, del);
}
