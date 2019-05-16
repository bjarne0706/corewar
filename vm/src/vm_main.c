/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:29:59 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/16 15:30:00 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			print_usage(void)
{
	ft_putendl("USAGE: ./corewar [-n 1] champ1.cor [-n 2] champ2.cor <...>");
	ft_putendl("\nFLAGS:");
	ft_putendl("	-n #	: specifies player's number (optional)");
}

int				main(int ac, char *av[])
{
	t_bool b = -99;

	if (ac > 1)
	{
		if (b)
			ft_putstr("Yes\n");
		else
			ft_putstr("No\n");
	}
	else
		print_usage();
	(void)av;
	return (0);
}
