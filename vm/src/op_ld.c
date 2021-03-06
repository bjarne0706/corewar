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

static void		log_op_ld(t_carr *c, int32_t arg, int r)
{
	ft_printf("{yellow}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}ld\e[27m %d, r%d{0}\n", arg, r);
}

void			op_ld(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		arg_dir;
	int16_t		arg1_ind;
	int8_t		reg;
	size_t		pc;

	pc = c->pc + 2;
	if (c->arg_types[0] == T_DIR)
	{
		arg_dir = get_int(v, pc, op->t_dir_size);
		pc += op->t_dir_size;
	}
	else
	{
		arg1_ind = get_int(v, pc, IND_SIZE);
		arg_dir = get_int(v, calc_address(c->pc, true, arg1_ind), DIR_SIZE);
		pc += IND_SIZE;
	}
	reg = v->arena[calc_address(pc, false, 0)];
	c->reg[reg - 1] = arg_dir;
	c->carry = (arg_dir == 0) ? true : false;
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_ld(c, arg_dir, reg);
}
