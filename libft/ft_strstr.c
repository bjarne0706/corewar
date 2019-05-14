/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:00:06 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 17:21:29 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] == str2[i] && str2[i])
		i++;
	if (i == ft_strlen(str2))
		return (1);
	return (0);
}

char		*ft_strstr(const char *str1, const char *str2)
{
	size_t		i;
	int			i2;
	size_t		save;

	i2 = -1;
	i = 0;
	save = 0;
	if (str1[i] == '\0' && str2[i] == '\0')
		return ((char *)str1);
	while (str1[i] != '\0')
	{
		save = i;
		while (str1[save] == str2[++i2] && str2[i2])
		{
			save++;
			if (str2[i2] == str1[0])
				if (ft_check(&str1[save], str2) == 1)
					return ((char *)str1 + save);
		}
		if (i2 == (int)ft_strlen(str2))
			return ((char *)str1 + i);
		i2 = -1;
		i++;
	}
	return (NULL);
}
