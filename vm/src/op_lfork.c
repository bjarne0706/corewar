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

void			lcopy_carriage(t_vm *v, t_carr *c, int32_t pos)
{
	t_carr		*cp;
	int			i;

	if (!(cp = (t_carr *)malloc(sizeof(t_carr))))
		vm_error("Carriage initialization failed");
	cp->id = v->carrs->id + 1;
	cp->champ = c->champ;
	cp->pc = pos;
	cp->op = 0;
	cp->wait_cycles = 0;
	ft_bzero(cp->arg_types, 3);
	cp->step = 0;
	cp->last_live = c->last_live;
	cp->carry = c->carry;
	cp->reg[0] = c->reg[0];
	i = 0;
	while (i < REG_NUMBER)
	{
		cp->reg[i] = c->reg[i];
		i++;
	}
	cp->nxt = v->carrs;
	v->carrs = cp;
}

void			op_lfork(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		pc;
	int32_t		arg1;

	pc = c->pc + 1;
	arg1 = get_arg(v, c, 0, &pc);
	lcopy_carriage(v, c, calc_address(c->pc, false, arg1));
	c->step = step_calc(c, op);
}
