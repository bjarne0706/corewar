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
		str[i] = v->arena[calc_address(pc + i, false, 0)];
		num += str[i];
		if (++i < size)
			num <<= 8;
	}
	return (num);
}
