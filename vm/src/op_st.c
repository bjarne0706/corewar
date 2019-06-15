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

static void		log_op_st(t_carr *c, int8_t r[], int16_t ind)
{
	ft_printf("{cyan}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}st\e[27m r%d (%d) ", r[0], c->reg[r[0] - 1]);
	if (c->arg_types[1] == T_REG)
		ft_printf("--> r%d{0}\n", r[1]);
	else
		ft_printf("--> %d(pc) %+d(ind){0}\n", c->pc, ind);
}

void		op_st(t_vm *v, t_carr *c, t_op *op)
{
	int16_t		ind;
	int8_t		r[2];
	int32_t		pc;

	pc = c->pc + 2;
	r[0] = v->arena[calc_address(pc, false, 0)];
	pc += 1;
	if (c->arg_types[1] == T_REG)
	{
		r[1] = v->arena[calc_address(pc, false, 0)];
		c->reg[r[1] - 1] = c->reg[r[0] - 1];
	}
	else
	{
		ind = get_int(v, pc, IND_SIZE);
		pc = calc_address(c->pc, true, ind);
		int_to_arena(v, pc, c, c->reg[r[0] - 1]);
	}
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_st(c, r, ind);
}
