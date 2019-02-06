/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:30:34 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/31 12:30:38 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_words(char const *s, char c)
{
	int words;
	int	word_started;

	words = 0;
	word_started = 0;
	while (*s)
	{
		if (*s != c && !word_started)
		{
			words++;
			word_started = 1;
		}
		if (*s == c)
			word_started = 0;
		s++;
	}
	return (words);
}
