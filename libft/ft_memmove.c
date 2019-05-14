/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:37:42 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/08 16:09:09 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t	i;
	char	*dst;
	char	*srcs;

	i = -1;
	dst = (char *)dest;
	srcs = (char *)src;
	if (srcs < dst)
		while ((int)num-- > 0)
			*(dst + num) = *(srcs + num);
	else
		while (++i < num)
			*(dst + i) = *(srcs + i);
	return (dst);
}
