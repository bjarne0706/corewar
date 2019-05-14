/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:33:48 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/09 15:07:20 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ss;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(ss = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		ss[i] = (*f)(i, *(s + i));
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
