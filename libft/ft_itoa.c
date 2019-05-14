/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 15:17:53 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 13:37:14 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					int_size(int n)
{
	int				i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char				*ft_itoa(int n)
{
	char			*number;
	int				i;
	unsigned int	ncpy;

	ncpy = n;
	i = int_size(n);
	if (n < 0)
	{
		ncpy = -n;
		i++;
	}
	if (!(number = ft_memalloc(i + 1)))
		return (NULL);
	number[--i] = ncpy % 10 + 48;
	while (ncpy /= 10)
		number[--i] = ncpy % 10 + 48;
	if (n < 0)
		number[0] = '-';
	return (number);
}
