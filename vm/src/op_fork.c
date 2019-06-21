/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:34:12 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/05 19:34:14 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_fork(t_carr *c, int32_t arg1)
{
	ft_printf("{magenta}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}fork\e[27m %d (%d) {0}\n", arg1, c->pc + arg1);
}

void			op_fork(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;

	pc = c->pc + 1;
	arg1 = get_arg(v, c, 0, &pc);
	copy_carriage(v, c, calc_address(c->pc, true, arg1));
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_fork(c, arg1);
}
