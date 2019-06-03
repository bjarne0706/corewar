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

void			op_aff(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		reg;
	if (v->options[3] && !v->options[0] && !v->options[1] && !v->options[2])
	{
		reg = v->arena[(c->pc + 2) % MEM_SIZE];
		ft_printf("Aff: %c\n", c->reg[reg - 1]);
	}
	c->step = step_calc(c, op);
}
