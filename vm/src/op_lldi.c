/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:13:45 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/05 21:13:46 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_lldi(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg[2];
	int8_t		reg;
	int32_t		addr;

	pc = c->pc + 2;
	arg[0] = get_arg(v, c, 0, &pc);
	arg[1] = get_arg(v, c, 1, &pc);
	reg = v->arena[calc_address(pc, false, 0)];
	addr = calc_address(c->pc + arg[0] + arg[1], false, 0);
	c->reg[reg - 1] = get_int(v, addr, REG_SIZE);
	c->carry = (c->reg[reg - 1] == 0) ? true : false;
	c->step = step_calc(c, op);

		// ft_printf("{I}	%02x %s{0}\n", op->code, op->name);		//
		// ft_printf("{I}pc: %d; arg[0]: %d{0}\n", pc, arg[0]);		//
		// ft_printf("{I}pc: %d; arg[1]: %d{0}\n", pc, arg[1]);		//
		// ft_printf("{I}pc: %d; arg3(r): %d{0}\n", pc, reg);		//
		// ft_printf("{I}c->reg[r - 1]: %08x{0}\n", c->reg[reg - 1]);		//
}
