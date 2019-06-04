/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:42:24 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/04 21:42:25 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void		op_xor(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		arg1;
	int32_t		arg2;
	int32_t		arg;
	size_t		pc;
	int8_t		reg;

	pc = c->pc + 2;
	arg1 = get_arg_and(v, c, 0, pc);
	if (c->arg_types[0] == T_DIR)
		pc += op->t_dir_size;
	else
		pc += (c->arg_types[0] == T_REG) ? 1 : IND_SIZE;
	arg2 = get_arg_and(v, c, 1, pc);
	if (c->arg_types[1] == T_DIR)
		pc += op->t_dir_size;
	else
		pc += (c->arg_types[1] == T_REG) ? 1 : IND_SIZE;
	reg = v->arena[calc_address(pc, false, 0)];
	arg = arg1 ^ arg2;
	c->reg[reg - 1] = arg;
	c->carry = (arg == 0) ? true : false;
	c->step = step_calc(c, op);
}

