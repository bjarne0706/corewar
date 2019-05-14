/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:06:52 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/08 16:55:47 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned long	i;
	unsigned char	*srcs;

	i = 0;
	srcs = (unsigned char*)src;
	while (i < num)
	{
		ft_memset(&dest[i], srcs[i], 1);
		i++;
	}
	return (dest);
}
