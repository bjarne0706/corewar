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

void			setup_arena(t_vm *v)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (i < v->champs_num)
	{
		ft_memcpy(&v->arena[pos], v->champs[i]->code, v->champs[i]->size);
		pos += MEM_SIZE / v->champs_num;
		i++;
	}
}

t_champ			*add_champ(int n)
{
	t_champ		*champ;

	if (!(champ = (t_champ *)ft_memalloc(sizeof(t_champ))))
		vm_error("Champion initialization failed");
	champ->num = n;
	ft_bzero(champ->name, PROG_NAME_LENGTH);
	ft_bzero(champ->comment, COMMENT_LENGTH);
	champ->size = 0;
	ft_bzero(champ->code, CHAMP_MAX_SIZE);
	return (champ);
}

t_vm			*init_vm(void)
{
	t_vm		*v;
	int			i;


	if(!(v = (t_vm *)ft_memalloc(sizeof(t_vm))))
		vm_error("VM initialization failed");
	i = 0;
	while (i < MEM_SIZE)
		v->arena[i++] = 0; 
	v->champs_num = 0;
	v->carrs = NULL;
	ft_bzero(v->options, 3);
	v->dump_cycles[0] = -1;
	v->dump_cycles[1] = -1;
	
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->champs[i] = NULL;
		i++;
	}
	return (v);
}