/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:44:12 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/02 18:44:14 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_ld(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		arg_dir;
	int16_t		arg1_ind;
	int8_t		reg;
	size_t		pc;

	pc = c->pc + 2;
	if (c->arg_types[0] == T_DIR)
	{
		arg_dir = get_int(v, pc, DIR_SIZE);
			printf("ARG_DIR: %d\n", arg_dir);
		pc += DIR_SIZE;
	}
	else
	{
		arg1_ind = get_int(v, pc, IND_SIZE);
		arg_dir = v->arena[calc_address(c->pc, true, arg1_ind)];
		pc += IND_SIZE;
	}
	reg = v->arena[calc_address(pc, false, 0)];
	c->reg[reg - 1] = arg_dir;
	c->carry = (arg_dir == 0) ? true : false;
	c->step = step_calc(c, op);
}
