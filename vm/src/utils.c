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

int32_t			get_arg(t_vm *v, t_carr *c, uint8_t idx, int32_t *pc)
{
	int32_t		arg;
	int8_t		r;
	int16_t		ind;
	t_op		*op;

	op = &g_ops[c->op - 1];
	if (c->arg_types[idx] == T_REG)
	{
		r = v->arena[calc_address(*pc, false, 0)];
		arg = c->reg[r - 1];
		(*pc)++;
	}
	else if (c->arg_types[idx] == T_DIR)
	{
		arg = get_int(v, calc_address(*pc, false, 0), op->t_dir_size);
		(op->t_dir_size == 2) ? arg = (int16_t)arg : 0;
		(*pc) += op->t_dir_size;
	}
	else
	{
		ind = get_int(v, calc_address(*pc, false, 0), IND_SIZE);
		arg = get_int(v, calc_address(c->pc, true, ind), DIR_SIZE);
		(*pc) += IND_SIZE;
	}
	return (arg);
}


void		int_to_arena(t_vm *v, int32_t pos, int32_t size, int32_t num)
{
	int		shift;

	shift = 0;
	while (size)
	{
		v->arena[calc_address(pos + size - 1, false, 0)] = (uint8_t)(num >> shift);
		shift += 8;
		size--;
	}
}

int32_t			get_int(t_vm *v, int pc, int size)
{
	int32_t				num;
 	int 				i;
	unsigned char		str[size];
// num = ((v->arena[(pc) % MEM_SIZE] << 24) + (v->arena[(pc + 1) % MEM_SIZE] << 16) + (v->arena[(pc + 2) % MEM_SIZE] << 8) +(v->arena[(pc + 3) % MEM_SIZE]));

 	num = 0;
 	i = 0;
 	while (i < size)
	{
		str[i] = v->arena[(pc + i) % MEM_SIZE];
		num += str[i];
		if (++i < size)
			num <<= 8;
	}
	return (num);
}

int32_t			calc_address(int32_t pc, t_bool idx_mode, int32_t step)
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

uint32_t			step_calc(t_carr *c, t_op *op)
{
	uint32_t		step;
	int				i;

	step = 1;
	step += (op->types_byte) ? 1 : 0; 
	// printf("TB: %d\n", op->types_byte);	
	// printf("OP: %2x __step__: %d\n", op->code, step);		//
	// printf("ar num: %d\n", op->ar_num);	
	i = 0;
	while (i < op->ar_num)
	{
		step += arg_size(c->arg_types[i], op);
		i++;
	}
		// ft_printf("{i}{darkgray}%02x %s: step:%d{0}\n", op->code, op->name, step);		//
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
