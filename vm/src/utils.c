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

int32_t			get_int(t_vm *v, int pc, int size)
{
	char 		str[size];
	int32_t		num;
	int 		i;
//	t_bool		sign;

	ft_bzero(str, size);
//	sign = v->arena[pc] & 0x80;
//		printf("SIGN: %d\n", sign);		//
	num = 0;
	i = -1;
	while (++i < size)
	{
		str[i] = v->arena[pc++ % MEM_SIZE];
//str[i] = (sign) ? v->arena[pc++ % MEM_SIZE] & 0xFF : v->arena[pc++ % MEM_SIZE];
		num |= str[i];
		if (i + 1 != size)
			num <<= 8;
			ft_printf("{green}%032b{0}\n", num);	//
	}
	return (/*(sign) ? ~(num) :*/ num);
}

uint32_t			step_calc(t_carr *c, t_op *op)
{
	uint32_t		step;
	int				i;

	step = 1;
	step += (op->types_byte) ? 1 : 0; 
	i = 0;
	while (i < op->ar_num)
	{
		step += arg_size(c->arg_types[i], op);
		i++;
	}
		printf("__step__: %d\n", step);		//
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
