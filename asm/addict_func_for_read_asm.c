/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addict_func_for_read_asm.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:44:25 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/06 14:44:27 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			label_char_pos(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != LABEL_CHAR)
		i++;
	return (i);
}

int			ft_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int			count_separ(char *str)
{
	int		i;
	int		counter;

	counter = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == SEPARATOR_CHAR)
			counter++;
	}
	return (counter);
}

int			trim_space(int i, char *line)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int			choose_name(char *line)
{
	if (ft_strcmp(line, "live") == 0)
		return (1);
	else if (ft_strcmp(line, "ld") == 0)
		return (2);
	else if (ft_strcmp(line, "st") == 0)
		return (3);
	else if (ft_strcmp(line, "add") == 0)
		return (4);
	else if (ft_strcmp(line, "sub") == 0)
		return (5);
	else if (ft_strcmp(line, "and") == 0)
		return (6);
	else if (ft_strcmp(line, "or") == 0)
		return (7);
	else if (ft_strcmp(line, "xor") == 0)
		return (8);
	else if (ft_strcmp(line, "zjmp") == 0)
		return (9);
	else if (ft_strcmp(line, "ldi") == 0)
		return (10);
	else if (ft_strcmp(line, "sti") == 0)
		return (11);
	else if (ft_strcmp(line, "fork") == 0)
		return (12);
	else if (ft_strcmp(line, "lld") == 0)
		return (13);
	else if (ft_strcmp(line, "lldi") == 0)
		return (14);
	else if (ft_strcmp(line, "lfork") == 0)
		return (15);
	else if (ft_strcmp(line, "aff") == 0)
		return (16);
	else
		return (0);
}
