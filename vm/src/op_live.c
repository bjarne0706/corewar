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

void			op_live(t_vm *v, t_carr *c, t_op *op)
{
	int			arg;
	int 		n = 300;
 (void)op;
	
	arg = ((v->arena[c->pc + 1] << 24) + (v->arena[c->pc + 2] << 16) + (v->arena[c->pc + 3] << 8) +(v->arena[c->pc + 4]));
		printf("%d\n", arg);	

	n = n + arg;

	// arg = get_int(v, (c->pc + 1) % MEM_SIZE, op->t_dir_size);
//	ft_printf("%x\n", v->arena[c->pc + 1]);
//	ft_printf("%x\n", v->arena[c->pc + 2]);
//	ft_printf("%x\n", v->arena[c->pc + 3]);
//	ft_printf("%x\n", v->arena[c->pc + 4]);

//	arg = ((int)(v->arena[c->pc + 1] << 24) + (int)(v->arena[c->pc + 2] << 16) + (int)(v->arena[c->pc + 3] << 8) +(int)(v->arena[c->pc + 4]));
//	if (arg == c->champ->num)
		// printf("::ARG: %d ||| %u\n", -200);
		printf("::ARG: %d ||| %d\n", c->pc, arg);


}
