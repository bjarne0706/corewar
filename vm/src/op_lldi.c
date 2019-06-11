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

static void		log_op_lldi(t_carr *c, int32_t arg1, int32_t arg2, int8_t reg)
{
	ft_printf("{cyan}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}lldi\e[27m %d %d r%d (%d){0}\n", arg1, arg2, reg,
		c->reg[reg - 1]);
	ft_printf("-> load from %d + %d = %d (with pc %d)\n", arg1, arg2, arg1 + arg2,
		c->pc + arg1 + arg2); //Without %mod! Need add %mod!!!
}

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
	if (v->log & LOG_OPS)
		log_op_lldi(c, arg[0], arg[1], reg);

		// ft_printf("{I}	%02x %s{0}\n", op->code, op->name);		//
		// ft_printf("{I}pc: %d; arg[0]: %d{0}\n", pc, arg[0]);		//
		// ft_printf("{I}pc: %d; arg[1]: %d{0}\n", pc, arg[1]);		//
		// ft_printf("{I}pc: %d; arg3(r): %d{0}\n", pc, reg);		//
		// ft_printf("{I}c->reg[r - 1]: %08x{0}\n", c->reg[reg - 1]);		//
}
