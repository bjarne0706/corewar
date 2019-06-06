/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:54:52 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/03 19:54:54 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_sub(t_vm *v, t_carr *c, t_op *op)
{
	int8_t		r1;
	int8_t		r2;
	int8_t		r3;
	int32_t		pc;

	pc = c->pc + 2;
	r1 = v->arena[calc_address(pc++, false, 0)];
	r2 = v->arena[calc_address(pc++, false, 0)];
	r3 = v->arena[calc_address(pc, false, 0)];
	c->reg[r3 - 1] = c->reg[r1 - 1] - c->reg[r2 - 1];
		// ft_printf("{blue}[%d]%d - [%d]%d = [%d]%d{0}\n", r1, c->reg[r1 - 1], r2, c->reg[r2 - 1], r3, c->reg[r3 - 1]);	///
	if (c->reg[r3 - 1] == 0)
		c->carry = true;
	else
		c->carry = false;
	c->step = step_calc(c, op);
}
