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

void			op_live(t_vm *v, t_carr *c, t_op *op)
{
	int		arg;
	
	if (v->options[3])
	{
		arg = get_int(v, (c->pc + 1) % MEM_SIZE, 1);
		ft_printf("Aff: %c\n", (char)(arg));
	}
	c->step = step_calc(c, op);
}
