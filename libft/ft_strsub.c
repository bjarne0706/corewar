/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:43:36 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/09 15:08:32 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;
	size_t	save;

	save = start;
	i = 0;
	ss = ft_memalloc(len + 1);
	if (!ss || !s)
		return (NULL);
	while (start < len + save)
	{
		ss[i] = s[start];
		start++;
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
