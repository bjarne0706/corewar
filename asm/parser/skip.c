/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 20:43:10 by evlasov           #+#    #+#             */
/*   Updated: 2019/01/09 20:43:12 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_space(char c)
{
	if (c == '\t' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r' ||
		c == ' ')
		return (1);
	return (0);
}

int		skip_space(const char *str, int i)
{
	while (check_space(str[i]) == 1)
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int		skip_comment(const char *str, int i)
{
//    ft_printf("skip\n");
	if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
	{
		while (str[i] != '\n')
			i++;
//		i++;
	}
	return (i);
}

int 	ft_skip(t_asm *st, int i)
{
    int     k;

    k = i;
	while (skip_space(st->str, i) != i || skip_comment(st->str, i) != i)
	{
        if (skip_space(st->str, i) != i)
            i = skip_space(st->str, i);
        else
            i = skip_comment(st->str, i);
    }
	if (k == i)
        return (-1);
	return (i);
}
