/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:41:23 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 17:05:57 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int ch, size_t num)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*srcs;
	unsigned char	ch1;

	ch1 = (unsigned char)ch;
	dst = (unsigned char*)dest;
	srcs = (unsigned char*)src;
	i = 0;
	while (i < num)
	{
		dst[i] = srcs[i];
		if (dst[i] == ch1)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
