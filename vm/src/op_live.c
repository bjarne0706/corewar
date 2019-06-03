/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:36:17 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/31 16:36:19 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_live(t_vm *v, t_carr *c, t_op *op)
{
	int			arg;
	t_champ		*ch;

	arg = get_int(v, (c->pc + 1) % MEM_SIZE, op->t_dir_size);
		ft_printf("{yellow}ARG::: %d{0}\n", arg);		//
	c->last_live = v->cycles;
		ft_printf("{red}c->last_live: %d{0}\n", c->last_live);		//
	v->lives_in_cycle++;
	ch = NULL;
	if (arg < 0 && arg > -(v->champs_num))
	{
		ch = v->champs[-arg - 1];
		ch->last_live_cyc = v->cycles;
		ch->current_lives++;
	}
	c->step = step_calc(c, op);
}
