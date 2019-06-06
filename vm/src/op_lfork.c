/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:33:46 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/05 21:33:48 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			op_lfork(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;

		ft_printf("{green}	%02x %s{0}\n", op->code, op->name);		//
	pc = c->pc + 1;
	arg1 = get_arg(v, c, 0, &pc);
			ft_printf("{green}pc: %d; arg1[type %d]: %d{0}\n", pc, c->arg_types[0], arg1);		//
	copy_carriage(v, c, calc_address(c->pc + arg1, false, 0));
			print_carriages(v);		//
	c->step = step_calc(c, op);
}
