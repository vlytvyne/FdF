/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:26:01 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/30 20:29:33 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_str(char **s, char c)
{
	char	*word;
	char	*ch_occurence;
	int		size;
	int		i;

	i = 0;
	ch_occurence = ft_strchr(*s, c);
	if (ch_occurence == 0)
		size = (int)ft_strlen(*s);
	else
		size = (int)(ch_occurence - *s);
	if (!(word = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (i < size)
	{
		word[i] = **s;
		(*s)++;
		i++;
	}
	(*s)--;
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**words;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(words = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			words[i] = create_str((char**)&s, c);
			i++;
		}
		s++;
	}
	words[i] = NULL;
	return (words);
}
