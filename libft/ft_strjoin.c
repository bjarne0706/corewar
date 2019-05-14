/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 12:38:32 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/09 15:16:25 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_new;
	size_t	i;
	int		i2;

	i2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s_new = ft_memalloc(i + 1);
	s_new[0] = '\0';
	i = 0;
	while (s1[i])
	{
		s_new[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		s_new[i] = s2[i2];
		i2++;
		i++;
	}
	s_new[i] = '\0';
	free((char *)s1);
	return (s_new);
}
