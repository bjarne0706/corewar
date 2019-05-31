/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:36:17 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/31 16:36:19 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void		op_live(t_vm *v, t_carr *c, t_op *op)
{
	int32_t		*arg;

		printf("Hello function!\n");		//
		(void)v;
		(void)op;
//	c->pc += 3;
	arg = (int32_t *)&v->arena[++c->pc];
		printf("::ARG: %d ||| %u\n", c->pc, *arg);
	ft_printf("{green}%032b{0}\n", *arg);

}
