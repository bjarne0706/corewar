/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:34:45 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/17 17:34:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		int_limits(char *n)
{
	static char	*imax = "2147483647";
	static char	*imin = "2147483648";
	int			sign;

	sign = 0;
	if (n[0] == '-' || n[0] == '+')
	{
		if (n[0] == '-')
			sign = -1;
		else if (n[0] == '+')
			sign = 1;
		n++;
	}
	if (ft_strlen(n) > 10)
		return (0);
	if (ft_strlen(n) == 10)
	{
		if ((!sign || sign == 1) && (ft_strcmp(n, imax) > 0))
			return (0);
		if ((sign == -1) && (ft_strcmp(n, imin) > 0))
			return (0);
	}
	return (1);
}

int				ft_isint(char *s)
{
	int		i;
	char	*n;

	if (s == NULL)
		return (0);
	i = 0;
	while (ft_isblank(*s))
		s++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.' && ft_isdigit(s[i + 1]))
		return (0);
	n = ft_strsub(s, 0, i);
	if (!int_limits(n))
	{
		ft_strdel(&n);
		return (0);
	}
	ft_strdel(&n);
	return (1);
}
