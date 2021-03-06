/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:50:24 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/30 19:50:26 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int				validate_reg_args(t_vm *v, t_carr *c, t_op *op)
{
	int				i;
	int				pos;
	unsigned char	reg;

	pos = 1;
	pos += (op->types_byte) ? 1 : 0;
	i = 0;
	while (i < op->ar_num)
	{
		if (c->arg_types[i] == T_REG)
		{
			reg = v->arena[calc_address(c->pc + pos, false, 0)];
			if (reg < 1 || reg > REG_NUMBER)
				return (false);
		}
		pos += arg_size(c->arg_types[i], op);
		i++;
	}
	return (true);
}

void			byte_to_arr3(uint8_t arg_types[], unsigned char byte)
{
	int		i;

	arg_types[0] = byte >> 6;
	arg_types[1] = byte << 2;
	arg_types[1] >>= 6;
	arg_types[2] = byte << 4;
	arg_types[2] >>= 6;
	i = 0;
	while (i < 3)
	{
		if (arg_types[i] == IND_CODE)
			arg_types[i] = T_IND;
		i++;
	}
}

int				validate_args_types(t_vm *v, t_carr *c, t_op *op)
{
	int				i;

	if (op->types_byte)
	{
		byte_to_arr3(c->arg_types, v->arena[calc_address(c->pc + 1, false, 0)]);
		i = 0;
		while (i < op->ar_num)
		{
			if (!(c->arg_types[i] & op->types[i]))
				return (false);
			i++;
		}
		return (true);
	}
	else
	{
		c->arg_types[0] = op->types[0];
		return (true);
	}
}
