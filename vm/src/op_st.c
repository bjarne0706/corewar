/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:05:37 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/02 20:05:39 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_st(t_vm *v, t_carr *c, t_op *op)
{
	int16_t		arg_ind;
	int8_t		reg;
	int8_t		reg2;
	int32_t		pc;

	pc = c->pc + 2;
	reg = v->arena[pc % MEM_SIZE];
	pc += 1;
	if (c->arg_types[1] == T_REG)
	{
		reg2 = v->arena[pc % MEM_SIZE];
		c->reg[reg2 - 1] = c->reg[reg - 1];
	}
	else
	{
		arg_ind = get_int(v, pc, IND_SIZE);
		pc = calc_adrr(c->pc, arg_ind);
		if (pc < 0)
			pc += MEM_SIZE;
		v->arena[pc] = c->reg[reg - 1];
	}
	c->step = step_calc(c, op);
}
