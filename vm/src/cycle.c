/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:26:20 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/28 17:26:24 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

t_bool			validate_operation(t_vm *v, t_carr *c, t_op *op)
{
	(void)v;
	(void)c;
	(void)op;

	return (true);
}

void			process_carriage(t_vm *v, t_carr *c)
{
	t_op		*op;

	if (c->wait_cycles == -1)
	{
		c->op = v->arena[c->pc];
		if (c->op >= 0x01 && c->op <= 0x10)
			c->wait_cycles = g_op_tab[c->op -1].cycles;
		else
		{
			c->wait_cycles = 0;
			c->step = 1;
		}
	}
	if (c->wait_cycles > 0)
		c->wait_cycles--;
	op = NULL;
	if (c->wait_cycles == 0)
	{
			op = &g_op_tab[c->op - 1];
//			validate_operation(v, c, op);
		c->pc = (c->pc + c->step) % MEM_SIZE;
	}
}

void			run_cycle(t_vm *v)
{
	t_carr		*c;

	c = v->carrs;
	while (c)
	{
		process_carriage(v, c);
		c = c->nxt;
	}
	v->cycles++;
	v->cyc_since_check++;
}
