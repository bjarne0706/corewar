/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:56:14 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/03 18:56:17 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_add(t_carr *c, int8_t r[])
{
	ft_printf("{blue}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}add\e[27m r%d (%d) + ", r[0], c->reg[r[0] - 1]);
	ft_printf("r%d (%d) ==> ", r[1], c->reg[r[1] - 1]);
	ft_printf("r%d (%d){0}\n", r[2], c->reg[r[0] - 1] + c->reg[r[1] - 1]);
}

void			op_add(t_vm *v, t_carr *c, t_op *op)
{
	int8_t		r[3];
	int32_t		pc;

	pc = c->pc + 2;
	r[0] = v->arena[calc_address(pc++, false, 0)];
	r[1] = v->arena[calc_address(pc++, false, 0)];
	r[2] = v->arena[calc_address(pc, false, 0)];
	if (v->log & LOG_OPS)
		log_op_add(c, r);
	c->reg[r[2] - 1] = c->reg[r[0] - 1] + c->reg[r[1] - 1];
		// ft_printf("{blue}[%d]%d + [%d]%d = [%d]%d{0}\n", r1, c->reg[r1 - 1], r2, c->reg[r2 - 1], r3, c->reg[r3 - 1]);	///
	if (c->reg[r[2] - 1] == 0)
		c->carry = true;
	else
		c->carry = false;
	c->step = step_calc(c, op);
}
