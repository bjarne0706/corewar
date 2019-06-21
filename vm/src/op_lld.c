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

static void		log_op_lld(t_carr *c, int32_t arg1, int8_t reg)
{
	ft_printf("{yellow}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}lld\e[27m %d r%d (%d) {0}\n", arg1, reg, c->reg[reg - 1]);
}

void			op_lld(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;
	int8_t		r;
	int16_t		ind;

	pc = c->pc + 2;
	if (c->arg_types[0] == T_DIR)
		arg1 = get_arg(v, c, 0, &pc);
	else
	{
		ind = get_int(v, pc, IND_SIZE);
		arg1 = get_int(v, calc_address(c->pc, false, 0), REG_SIZE);
		pc += IND_SIZE;
	}
	r = v->arena[calc_address(pc, false, 0)];
	c->reg[r - 1] = arg1;
	c->carry = (arg1 == 0) ? true : false;
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_lld(c, arg1, r);
}
