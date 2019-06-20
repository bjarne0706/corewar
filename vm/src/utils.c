/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:43:29 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/18 19:43:31 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

inline int32_t		calc_address(int32_t pc, int idx_mode, int32_t step)
{
	int32_t		addr;

	if (idx_mode)
		addr = pc + (step % IDX_MOD);
	else
		addr = pc;
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

uint32_t			arg_size(uint8_t arg_type, t_op *op)
{
	uint32_t	size;

	size = 0;
	if (arg_type == T_REG)
		size = 1;
	else if (arg_type == T_DIR)
		size = op->t_dir_size;
	else if (arg_type == T_IND)
		size = IND_SIZE;
		//  printf("size of <%d> arg is: %d\n", arg_type, size);	//
	return (size);
}

uint32_t			step_calc(t_carr *c, t_op *op)
{
	uint32_t		step;
	int				i;

	step = 1;
	step += (op->types_byte) ? 1 : 0;
	//  printf("TB: %d\n", op->types_byte);
	//  printf("OP: %2x __step__: %d\n", op->code, step);		//
	//  printf("ar num: %d\n", op->ar_num);
	i = 0;
	while (i < op->ar_num)
	{
		step += arg_size(c->arg_types[i], op);
		i++;
	}
		//  ft_printf("{i}{darkgray}%02x %s: step:%d{0}\n", op->code, op->name, step);		//
	return (step);
}

unsigned int		reverse_byte(unsigned int num)
{
	unsigned	write;
	unsigned	bt;
	int			i;

	i = -1;
	write = 0;
	while (++i < 4)
	{
		bt = (num >> 8 * i) & 0xff;
		write |= bt << (24 - 8 * i);
	}
	return (write);
}
