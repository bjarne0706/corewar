/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:07:10 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 17:27:42 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char const *s, char c, size_t i)
{
	size_t		j;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		word_num;
	char		**parsed;
	int			j;

	word_num = -1;
	i = 0;
	if (s)
	{
		if (!(parsed = (char **)malloc(sizeof(char *) * ft_w_c(s, c) + 1)))
			return (NULL);
		while (++word_num < ft_w_c(s, c))
		{
			while (s[i] == c)
				i++;
			parsed[word_num] = (char *)malloc(word_len(s, c, i) + 1);
			j = 0;
			while (s[i] != c && s[i])
				parsed[word_num][j++] = s[i++];
			parsed[word_num][j] = '\0';
		}
		parsed[word_num] = NULL;
		return (parsed);
	}
	return (NULL);
}
