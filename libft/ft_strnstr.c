/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:21:10 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 15:20:33 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str1, const char *str2, size_t num)
{
	size_t	i;
	size_t	i2;
	int		save;
	size_t	k;

	i = -1;
	if (!ft_strlen(str2))
		return ((char *)str1);
	while (*(str1 + ++i) && i < num)
	{
		i2 = 0;
		if (*(str1 + i) == *str2)
		{
			k = i;
			save = 1;
			while (*(str1 + k) && *(str2 + i2) && k < num)
			{
				if (*(str1 + k++) != *(str2 + i2++))
					save = 0;
			}
			if (save && !*(str2 + i2))
				return ((char *)(str1 + i));
		}
	}
	return (NULL);
}
