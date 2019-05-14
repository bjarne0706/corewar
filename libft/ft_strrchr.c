/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 03:47:09 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/08 16:20:48 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *str, int sym)
{
	int		i;
	char	*str2;

	str2 = (char *)str;
	i = ft_strlen(str2);
	while (i > -1)
	{
		if (str2[i] == (char)sym)
			return (&str2[i]);
		i--;
	}
	return (NULL);
}
