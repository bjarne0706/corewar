/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:30:56 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/06 16:30:57 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			process_carriage(t_vm *v, t_carr *c)
{
	t_op		*op;

	op = NULL;
	if (c->wait_cycles == 0)
	{
		c->op = v->arena[c->pc];
		if (c->op >= 0x01 && c->op <= 0x10)
			c->wait_cycles = g_ops[c->op -1].cycles;
	}
	if (c->wait_cycles > 0)
		c->wait_cycles--;
	if (c->wait_cycles == 0)
	{
		if (c->op >= 0x01 && c->op <= 0x10)
		{
			op = &g_ops[c->op - 1];
			if (validate_args_types(v, c, op) && validate_reg_args(v, c, op))
			{
//					printf("))) Valid OP!\n");	//
				g_func_arr[op->code - 1](v, c, op);
//				g_func_arr[0](v, c, op);
			}
			else
			{
//					printf("((( Invalid OP!\n");		//
				c->step = step_calc(c, op);
			}
		}
		else
		{
			c->wait_cycles = 0;
			c->step = 1;
		}
		c->pc = (c->pc + c->step) % MEM_SIZE;
	}
}

void			run_cycle(t_vm *v)
{
	t_carr		*c;

	v->cycles++;
	v->cyc_since_check++;
	c = v->carrs;
	while (c)
	{
		process_carriage(v, c);
		c = c->nxt;
	}
}
