/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:28:24 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/04 16:28:26 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_ldi(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;
	int32_t		arg2;
	int8_t		r;

	pc = c->pc + 2;
	arg1 = get_arg(v, c, 0, &pc);
		// ft_printf("{I}pc: %d; arg1: %d{0}\n", pc, arg1);		//
	arg2 = get_arg(v, c, 1, &pc);
		// ft_printf("{I}pc: %d; arg2: %d{0}\n", pc, arg2);		//
	r = v->arena[calc_address(pc, false, 0)];
		// ft_printf("{I}pc: %d; arg3(r): %d{0}\n", pc, r);		//
	c->reg[r - 1] = get_int(v, calc_address(c->pc, true, arg1 + arg2), REG_SIZE);
		// ft_printf("{I}c->reg[r - 1]: %08x{0}\n", c->reg[r - 1]);		//
	c->step = step_calc(c, op);
}
