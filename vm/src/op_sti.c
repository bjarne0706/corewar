/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:49:46 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/05 15:49:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_sti(t_carr *c, int32_t arg[], int r)
{
	ft_printf("{cyan}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}sti\e[27m r%d (%d) %d %d\n",
											r, c->reg[r - 1], arg[0], arg[1]);
	ft_printf("	-> store to %d + %d = %d (with pc and mod %d){0}\n",
	arg[0], arg[1], arg[0] + arg[1], c->pc + ((arg[0] + arg[1]) % IDX_MOD));
}

void			op_sti(t_vm *v, t_carr *c, t_op *op)
{
	int8_t		r;
	int32_t		pc;
	int32_t		arg[2];

	pc = c->pc + 2;
	r = v->arena[calc_address(pc, false, 0)];
	pc++;
	arg[0] = get_arg(v, c, 1, &pc);
	arg[1] = get_arg(v, c, 2, &pc);
	int_to_arena(v, calc_address(c->pc,
								true, arg[0] + arg[1]), c, c->reg[r - 1]);
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_sti(c, arg, r);
}
