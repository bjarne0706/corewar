/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:26:20 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/28 17:26:24 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

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
		if (arg_types[i] == 3)
			arg_types[i] = T_IND;
		i++;
	}
}			

t_bool			validate_args_types(t_vm *v, t_carr *c, t_op *op)
{
	uint8_t			arg_types[3];
	int				i;

	if (op->types_byte)
	{
		byte_to_arr3(arg_types, v->arena[c->pc + 1]);
		ft_printf("> arg_type:\n[%08b]\n[%08b]\n[%08b]\n", arg_types[0], arg_types[1], arg_types[2]);

		i = 0;
		while ((i < op->ar_num) && (arg_types[i] & op->types[i]))
		{
				op->types[i] = arg_types[i];
				i++;
		}
			ft_printf("op_types[0]: %08b\n", op->types[0]);
			ft_printf("op_types[1]: %08b\n", op->types[1]);
			ft_printf("op_types[2]: %08b\n", op->types[2]);
			ft_printf("T_REG: %08b\n", T_REG);
			ft_printf("T_DIR: %08b\n", T_DIR);
			ft_printf("T_IND: %08b\n", T_IND);
		if (i < op->ar_num)
			return (false);
		else
			return (true);
	}
	else
	{
		ft_printf("op_types[0]: %08b\n", op->types[0]);
		return (true);
	}
}

void			process_carriage(t_vm *v, t_carr *c)
{
	t_op		*op;

	op = NULL;
	if (c->wait_cycles == 0)
	{
		c->op = v->arena[c->pc];
		if (c->op >= 0x01 && c->op <= 0x10)
			c->wait_cycles = g_ops[c->op -1].cycles;
	}
	if (c->wait_cycles > 0)
		c->wait_cycles--;
	if (c->wait_cycles == 0)
	{
		if (c->op >= 0x01 && c->op <= 0x10)
		{
			op = &g_ops[c->op - 1];
			if (validate_args_types(v, c, op))
			{
					printf("))) Valid OP!\n");	//
			}
			else
			{
					printf("((( Invalid OP!\n");		//
//				c->step = step_calc();
			}
		}
		else
		{
			c->wait_cycles = 0;
			c->step = 1;
		}
	}
	c->pc = (c->pc + c->step) % MEM_SIZE;
}

void			run_cycle(t_vm *v)
{
	t_carr		*c;

	c = v->carrs;
	while (c)
	{
		process_carriage(v, c);
		c = c->nxt;
	}
	v->cycles++;
	v->cyc_since_check++;
}
