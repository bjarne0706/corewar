/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:04:51 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/23 19:04:53 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			print_arena(t_vm *v, char flag)
{
	int		x;
	int		y;
	int		format;

	format = (flag == 'd' || flag == 's') ? 32 : 64;
	y = 0;
	while (y * format < MEM_SIZE)
	{
		x = 0;
		ft_printf("%06p : ", y * format);
		while (x < format)
		{
			ft_printf("%.2x ", v->arena[y * format + x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}
