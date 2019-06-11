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

static void		log_op_lfork(t_carr *c, int32_t arg1)
{
	ft_printf("{cyan}[p%d {i}ch%d\e[23m]> ", c->id, c->champ->num);
	ft_printf("{I}lfork\e[27m %d (%d) {0}\n", arg1, c->pc + arg1);
}

void			op_lfork(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;

		// ft_printf("{green}	%02x %s{0}\n", op->code, op->name);		//
	pc = c->pc + 1;
	arg1 = get_arg(v, c, 0, &pc);
			// ft_printf("{green}pc: %d; arg1[type %d]: %d{0}\n", pc, c->arg_types[0], arg1);		//
	copy_carriage(v, c, calc_address(c->pc + arg1, false, 0));
			// print_carriages(v);		//
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_lfork(c, arg1);
}
