/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:21:35 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/05 16:21:37 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_lld(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;
	int8_t		r;
	int16_t		ind;
		
		ft_printf("{b}	%02x %s{0}\n", op->code, op->name);		//
	pc = c->pc + 2;
	if (c->arg_types[0] == T_DIR)
		arg1 = get_arg(v, c, 0, &pc);
	else
	{
		ind = get_int(v, pc, IND_SIZE);
		arg1 = get_int(v, calc_address(c->pc, false, 0), REG_SIZE);
		pc += IND_SIZE;
	}
		ft_printf("{b}pc: %d; arg1[type %d]: %d{0}\n", pc, c->arg_types[0], arg1);		//
	r = v->arena[calc_address(pc, false, 0)];
	c->reg[r - 1] = arg1;
		ft_printf("{b}pc: %d; r(%d): %08x{0}\n", pc, r, c->reg[r - 1]);	//
	c->carry = (arg1 == 0) ? true : false;
	c->step = step_calc(c, op);
}
