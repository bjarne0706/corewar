/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:21:30 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 17:15:09 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strncat(char *s2, const char *s1, size_t num)
{
	int				i;
	unsigned long	i2;

	i2 = 0;
	i = 0;
	while (s2[i])
		i++;
	while (i2 < num && s1[i2])
	{
		s2[i] = s1[i2];
		i2++;
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
