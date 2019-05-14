/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:34:23 by dchantse          #+#    #+#             */
/*   Updated: 2019/02/21 17:00:08 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	num;

	num = 0;
	i = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] == '0')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = 10 * num + (str[i] - 48);
		IFRET((num >= 9223372036854775807 && sign == 1), (-1));
		IFRET((num > 9223372036854775807 && sign == -1), (0));
		i++;
	}
	return (num * sign);
}
