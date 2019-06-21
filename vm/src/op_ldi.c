/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:28:24 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/04 16:28:26 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_ldi(t_carr *c, int32_t arg[], int r)
{
	ft_printf("{yellow}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}ldi\e[27m %d %d r%d (%d)\n",
								arg[0], arg[1], r, c->reg[r - 1]);
	ft_printf("	-> load from %d + %d = %d (with pc and mod %d){0}\n",
								arg[0], arg[1], arg[0] + arg[1],
								c->pc + ((arg[0] + arg[1]) % IDX_MOD));
}

void			op_ldi(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg[2];
	int8_t		r;

	pc = c->pc + 2;
	arg[0] = get_arg(v, c, 0, &pc);
	arg[1] = get_arg(v, c, 1, &pc);
	r = v->arena[calc_address(pc, false, 0)];
	c->reg[r - 1] =
		get_int(v, calc_address(c->pc, true, arg[0] + arg[1]), REG_SIZE);
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_ldi(c, arg, r);
}
