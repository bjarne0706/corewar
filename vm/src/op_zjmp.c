/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:21:53 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/03 20:21:55 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_zjmp(t_carr *c, int32_t arg_dir)
{
	ft_printf("{magenta}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}zjmp\e[27m %d ", arg_dir);
	if (c->carry)
		ft_printf("OK{0}\n");
	else
		ft_printf("FAILED{0}\n");
}

void			op_zjmp(t_vm *v, t_carr *c, t_op *op)
{
	int16_t			arg_dir;

	arg_dir = get_int(v, c->pc + 1, op->t_dir_size);
	if (c->carry)
	{
		c->pc = calc_address(c->pc, true, arg_dir);
		c->step = 0;
	}
	else
		c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_zjmp(c, arg_dir);
}
