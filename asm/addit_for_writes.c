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

int 			search_bracks(char *line)
{
	int 		i;

	i = -1;
	while (line[++i])
		if (line[i] == '"')
			return (i);
	return (0);
}

int 			search_r_bracks(char *line, int num)
{
	int 		i;

	i = ft_strlen(line);
	while (line[--i])
		if (line[i] == '"' && i != num)
			return (i);
	return (0);
}

char 			*read_betw_brack(char *str)
{
	char	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new = (char *)ft_memalloc(PROG_NAME_LENGTH);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"' && str[i])
	{
		new[y] = str[i];
		y++;
		i++;
	}
	new[y] = '\0';
	free(str);
	return (new);
}

unsigned int	reverse_byte(unsigned int num)
{
	unsigned   write;
	unsigned   bt;
	int     i;

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
	printf("%s\n", str);
	// system("leaks asm");
	free_structs();
	exit(1);
}