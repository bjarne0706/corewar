/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:04:38 by dstepane          #+#    #+#             */
/*   Updated: 2018/10/27 19:04:39 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			m;

	m = 0;
	p = (unsigned char*)dst;
	while (m < n)
	{
		*p = *((unsigned char*)src + m);
		p++;
		m++;
	}
	return (dst);
}
