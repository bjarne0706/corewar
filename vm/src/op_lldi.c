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
	int32_t		arg1;
	int32_t		arg2;
	int8_t		reg;
	int32_t		addr;

	pc = c->pc + 2;
	arg1 = get_arg(v, c, 0, &pc);
	arg2 = get_arg(v, c, 1, &pc);
	reg = v->arena[calc_address(pc, false, 0)];
	addr = calc_address(c->pc, false, arg1 + arg2);
	c->reg[reg - 1] = get_int(v, addr, REG_SIZE);
	c->step = step_calc(c, op);
}
