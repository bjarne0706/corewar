/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:01:25 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/03 20:01:27 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_and(t_carr *c, int32_t arg1, int32_t arg2, int8_t reg)
{
	ft_printf("{blue}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}and\e[27m %d %d r%d (%d) {0}\n", arg1, arg2, reg,
		c->reg[reg - 1]);
}

void			op_and(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		arg1;
	int32_t		arg2;
	int32_t		arg;
	int32_t		pc;
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
	arg = arg1 & arg2;
	c->reg[reg - 1] = arg;
	c->carry = (arg == 0) ? true : false;
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_and(c, arg1, arg2, reg);
}
