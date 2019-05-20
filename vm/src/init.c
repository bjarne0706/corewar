/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:33:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/17 16:33:49 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"
/*
void			init_champs(t_vm *v)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!(v->champs[i] = (t_champ *)ft_memalloc(sizeof(t_champ))))
			vm_error("Champions initialization failed");
		v->champs[i]->num = 0;
		v->champs[i]->name = NULL;
		v->champs[i]->comment = NULL;
		v->champs[i]->size = 0;
		i++;
	}
}
*/

t_champ			*add_champ(int n)
{
	t_champ		*champ;

	if (!(champ = (t_champ *)ft_memalloc(sizeof(t_champ))))
		vm_error("Champion initialization failed");
	champ->num = n;
	ft_bzero(champ->name, PROG_NAME_LENGTH);
	ft_bzero(champ->comment, COMMENT_LENGTH);
	champ->size = 0;
	return (champ);
}

void			null_champs(t_vm *v)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->champs[i] = NULL;
		i++;
	}
}

t_vm			*init_vm(void)
{
	t_vm		*v;

	
	if(!(v = (t_vm *)ft_memalloc(sizeof(t_vm))))
		vm_error("VM initialization failed");
	v->champs_num = 0;
	v->carrs = NULL;
	ft_bzero(v->options, 3);
	v->dump_cycles[0] = -1;
	v->dump_cycles[1] = -1;
	null_champs(v);
	return (v);
}