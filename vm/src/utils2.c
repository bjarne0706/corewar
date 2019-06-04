/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:03:37 by evlasov           #+#    #+#             */
/*   Updated: 2019/06/04 21:03:38 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int32_t		get_arg_and(t_vm *v, t_carr *c, size_t num, size_t pc)
{
	int16_t		arg_ind;
	int8_t		reg;
	int32_t		arg;

	if (c->arg_types[num] == T_REG)
	{
		reg = v->arena[calc_address(pc, false, 0)];
		arg = c->reg[reg - 1];
	}
	else if (c->arg_types[num] == T_DIR)
	{
		arg = get_int(v, pc, 4);
	}
	else
	{
		arg_ind = get_int(v, pc, IND_SIZE);
		arg = v->arena[calc_address(c->pc, true, arg_ind)];
	}
	return (arg);
}
