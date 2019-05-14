/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 04:01:53 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 13:47:47 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t num)
{
	size_t	i;
	size_t	i2;
	size_t	dstsize;
	size_t	srcsize;

	i2 = 0;
	i = 0;
	dstsize = ft_strlen(dest);
	srcsize = ft_strlen(src);
	if (num == 0)
		return (srcsize);
	if (num < dstsize + 1)
		return (num + srcsize);
	while (dest[i] && i < num - 1)
		i++;
	while (src[i2] && i + i2 < num - 1)
	{
		dest[i + i2] = src[i2];
		i2++;
	}
	dest[i + i2] = '\0';
	return (dstsize + srcsize);
}
