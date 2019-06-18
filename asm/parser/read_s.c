/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 21:03:11 by evlasov           #+#    #+#             */
/*   Updated: 2019/01/09 21:03:12 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_s(char *filename, t_asm *st)
{
	int 	i;

	i = 0;
	if(!(st->str = ft_filetostr(filename)))
		return (-1);
	ft_printf("%s\n", st->str);
	st->str_count = 0;
	while (st->str[i])
	{
		if (st->str[i] == '\n')
			st->str_count++;
		i++;
	}
	return (0);
}
