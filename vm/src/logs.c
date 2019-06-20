/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:38:24 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/10 15:38:25 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			log_moves(t_vm *v, t_carr *c)
{
	uint32_t		i;

	ft_printf(">> [p%d {i}ch%d\e[23m] ADV %d (%#0.4x -> %#0.4x) ",
						c->id, c->champ->num, c->step, c->pc, c->pc + c->step);
	i = 0;
	while (i < c->step)
	{
		ft_printf("%02x ", v->arena[calc_address(c->pc + i, false, 0)]);
		i++;
	}
	ft_printf("\n");
}

void			log_deaths(t_vm *v, t_carr *del)
{
	ft_printf("{red}{b}p%d{0} {red}({i}champ %d\e[23m) ",
													del->id, del->champ->num);
	ft_printf("hasn't lived for %zd cycles (CTD: %d){0}\n",
									v->cycles - del->last_live, v->cyc_to_die);
}

void			log_cycles(size_t cycles)
{
	ft_printf("{d}Cycle: %zd{0}\n", cycles);
}
