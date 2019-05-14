/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:57:57 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 16:35:18 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strtrim(char const *s)
{
	int		i;
	int		size;
	char	*new_str;
	int		i2;

	if (!s)
		return (NULL);
	size = ft_strlen(s) - 1;
	i = -1;
	i2 = -1;
	while (s[size] == ' ' || s[size] == '\t' || s[size] == '\n')
		size--;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		size--;
	if (size <= 0)
		size = 0;
	s += i;
	if (!(new_str = ft_strnew(size + 1)))
		return (NULL);
	while (++i2 < size + 1)
		new_str[i2] = *s++;
	new_str[i2] = '\0';
	return ((char *)new_str);
}
