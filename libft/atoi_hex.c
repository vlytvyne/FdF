/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:56:45 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/31 14:41:19 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_hexnum(char ch)
{
	return (ch >= 'A' && ch <= 'F');
}

int			atoi_hex(char *str)
{
	int	res;
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	res = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	if (str[0] == '0' && str[1] == 'X')
		i = 2;
	else
		i = 0;
	while (ft_isdigit(str[i]) || is_hexnum(str[i]))
	{
		if (ft_isdigit(str[i]))
			res = (res * 16) + (str[i] - '0');
		else
			res = (res * 16) + (str[i] - 'A' + 10);
		i++;
	}
	return (res);
}
