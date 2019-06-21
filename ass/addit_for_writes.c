/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_for_writes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:48:58 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 17:49:04 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	reverse_byte(unsigned int num)
{
	unsigned	write;
	unsigned	bt;
	int			i;

	i = -1;
	write = 0;
	while (++i < 4)
	{
		bt = (num >> 8 * i) & 0xff;
		write |= bt << (24 - 8 * i);
	}
	return (write);
}

void			error(char *str)
{
	ft_printf("%s\n", str);
	free_structs();
	exit(1);
}

void			check_size(char **str, int size, int type)
{
	if (type)
	{
		if (size >= COMMENT_LENGTH)
		{
			ft_strdel(str);
			error("Error: too long comment.");
		}
	}
	else
	{
		if (size >= PROG_NAME_LENGTH)
		{
			ft_strdel(str);
			error("Error: too long name.");
		}
	}
}

int				validate_name_cmd(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i] != NAME_CMD_STRING[0])
		if (!ft_space(str[i]))
			error("Syntax error in name command.");
	i--;
	while (str[++i] != '"' && !ft_space(str[i]) && str[i])
		if (str[i] != NAME_CMD_STRING[j++])
			error("Syntax error in name command.");
	while (str[i] != '"' && ft_space(str[i]) && str[i])
		i++;
	if (str[i] == '\0' || str[i] != '"')
		error("Syntax error in name command.");
	return (i);
}

void			put_hex(int32_t nbr, int size)
{
	unsigned int	tmp;
	int				i;
	unsigned int	max;
	char			*res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		tmp = max + nbr + 1;
	else
		tmp = nbr;
	res = (char *)malloc(size);
	i = size;
	while (--i >= 0)
	{
		res[i] = tmp % 256;
		tmp /= 256;
	}
	ft_memcpy(g_full_line + g_posit, res, size);
	g_posit += size;
	free(res);
}
