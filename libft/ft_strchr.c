/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 03:33:09 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/08 16:20:39 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int sym)
{
	int		i;
	char	*str2;

	str2 = (char *)str;
	i = 0;
	while (str2[i])
	{
		if (str2[i] == (char)sym)
			return (&str2[i]);
		i++;
	}
	if (str2[i] == (char)sym)
		return (&str2[i]);
	return (NULL);
}
