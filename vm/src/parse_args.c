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

int			validate_reg_args(t_vm *v, t_carr *c, t_op *op)
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
			reg = v->arena[c->pc + pos];
//				printf("..reg: %.2x\n", reg);	//
			if (reg < 1 || reg > REG_NUMBER)
				return (false);
		}
		pos += arg_size(c->arg_types[i], op);
		i++;
	}
	return (true);
}

void			byte_to_arr3(uint8_t *arg_types, unsigned char byte)
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

int			validate_args_types(t_vm *v, t_carr *c, t_op *op)
{
	uint8_t			arg_types[3];
	int				i;

		// 	ft_printf("T_REG: %08b\n", T_REG);		//
		// ft_printf("T_DIR: %08b\n", T_DIR);
		// 	ft_printf("T_IND: %08b\n", T_IND);
	if (op->types_byte)
	{
		byte_to_arr3(arg_types, v->arena[c->pc + 1]);
		// ft_printf("> arg_type:\n[%08b]\n[%08b]\n[%08b]\n", arg_types[0], arg_types[1], arg_types[2]);

		i = 0;
		while ((i < op->ar_num) && (arg_types[i] & op->types[i]))
		{
			c->arg_types[i] = arg_types[i];
			i++;
		}
			// ft_printf("c->ar_types[0]: %08b\n", c->arg_types[0]);	//
			// ft_printf("c->ar_types[1]: %08b\n", c->arg_types[1]);
			// ft_printf("c->ar_types[2]: %08b\n", c->arg_types[2]);
		if (i < op->ar_num)
			return (false);
		else
			return (true);
	}
	else
	{
		c->arg_types[0] = op->types[0];
			// ft_printf("c->ar_types[0]: %08b\n", c->arg_types[0]);
		return (true);
	}
}
