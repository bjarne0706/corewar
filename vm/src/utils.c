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

size_t			calc_adrr(int pc, int16_t arg_ind)
{
	int		adrr;

	adrr = ((pc + arg_ind) % MEM_SIZE) % IDX_MOD;
	if (adrr < 0)
		adrr += MEM_SIZE;
	return (adrr);
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
		printf("OP: %2x __step__: %d\n", op->code, step);		//
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
