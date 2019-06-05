/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:49:46 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/05 15:49:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_sti(t_vm *v, t_carr *c, t_op *op)
{
	int8_t		r;
	int32_t		pc;
	int32_t		arg2;
	int32_t		arg3;

		ft_printf("{cyan}	%02x %s{0}\n", op->code, op->name);		//
	pc = c->pc + 2;
	r = v->arena[calc_address(pc, false, 0)];
		ft_printf("{cyan}pc: %d; r(%d): %d{0}\n", pc, r, c->reg[r - 1]);		//
	pc++;
	arg2 = get_arg(v, c, 1, &pc);
		ft_printf("{cyan}pc: %d; arg2: %d{0}\n", pc, arg2);		//
	arg3 = get_arg(v, c, 2, &pc);
		ft_printf("{cyan}pc: %d; arg3: %d{0}\n", pc, arg3);		//
	int_to_arena(v, calc_address(c->pc, true, arg2 + arg3), REG_SIZE, c->reg[r - 1]);
		ft_printf("{cyan}c->reg[r - 1]: %08x{0}\n", c->reg[r - 1]);		//
	c->step = step_calc(c, op);
}
