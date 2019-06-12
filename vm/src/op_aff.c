/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:40:15 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/01 19:40:16 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_aff(t_carr *c, int32_t r)
{
	ft_printf("{white}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}aff\e[27m %d (%d) {0}\n", r, c->reg[r - 1]);
}

void			op_aff(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		reg;

	if (v->options[3] && !v->options[0] && !v->options[1] && !v->options[2])
	{
		reg = v->arena[calc_address((c->pc + 2), false, 0)];
		ft_printf("Aff: %c\n", c->reg[reg - 1]);
	}
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_aff(c, reg);
}
