/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:04:24 by dstepane          #+#    #+#             */
/*   Updated: 2019/06/06 15:04:25 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void				slaughter_carriage(t_vm *v, t_carr *prev, t_carr *del)
{
	if (del == v->carrs)
	{
		v->carrs = v->carrs->nxt;
		ft_memdel((void **)&del);
	}
	else if (del->nxt == NULL)
	{
		ft_memdel((void **)&del);
		prev->nxt = NULL;
	}
	else
	{
		prev->nxt = del->nxt;
		ft_memdel((void **)&del);
	}
}

void			kill_those_loosers(t_vm *v)
{
	t_carr		*prev;
	t_carr		*cur;
	t_carr		*del;

	cur = v->carrs;
	prev = NULL;
	while (cur && v->carrs_num > 0)
	{
		if (v->cycles - cur->last_live >= v->cyc_to_die || v->cyc_to_die <= 0)
		{
			del = cur;
			cur = cur->nxt;
			slaughter_carriage(v, prev, del);
			v->carrs_num--;
		}
		else
		{
			prev = cur;
			cur = cur->nxt;
		}
	}
//		print_carriages(v);	//
}

void			copy_carriage(t_vm *v, t_carr *c, int32_t pos)
{
	t_carr		*cp;
	int			i;

	if (!(cp = (t_carr *)malloc(sizeof(t_carr))))
		vm_error("Carriage initialization failed");
	cp->id = v->carrs->id + 1;
	cp->champ = c->champ;
	cp->pc = pos;
	cp->op = 0;
	cp->wait_cycles = 0;
	ft_bzero(cp->arg_types, 3);
	cp->step = 0;
	cp->last_live = c->last_live;
	cp->carry = c->carry;
	i = -1;
	while (++i < REG_NUMBER)
		cp->reg[i] = c->reg[i];
	cp->nxt = v->carrs;
	v->carrs = cp;
}
