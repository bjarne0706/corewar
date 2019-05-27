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

void			add_carriage(t_carr **carr, t_champ *chmp, unsigned int pos)
{
	t_carr		*new;
	static int	id = 0;

	if (!(new = (t_carr *)malloc(sizeof(t_carr))))
		vm_error("Carriage initialization failed");
	new->id = ++id;
	new->champ = chmp;
	new->pc = pos;
	new->wait_cycles = 0;
	new->step = 0;
	new->last_live = 0;
	new->carry = false;
	new->reg[0] = -(chmp->num);
	ft_bzero(&new->reg[1], sizeof(new->reg) - sizeof(int));
	new->nxt = *carr;
	*carr = new; 
}

void			setup_carriages(t_vm *v)
{
	int				n;
	unsigned int	pos;

	n = 1;
	pos = 0;
	while (n <= v->champs_num)
	{
		add_carriage(&(v->carrs), v->champs[n - 1], pos);
		v->carrs_num++;
		pos += MEM_SIZE / v->champs_num;
		n++; 
	}
}

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
	ft_bzero(v->options, 3);
	v->dump_cycles[0] = -1;
	v->dump_cycles[1] = -1;
	i = 0;
	while (i < MEM_SIZE)
		v->arena[i++] = 0; 
	v->champs_num = 0;
		i = 0;
		while (i < MAX_PLAYERS)
		{
			v->champs[i] = NULL;
			i++;
		}
	v->last_standing = NULL;
	v->carrs = NULL;
	v->carrs_num = 0;
	v->cycles = 0;
	v->cycles_to_die = CYCLE_TO_DIE;
	v->lives_in_cycle = 0;
	v->checks_done = 0;
	return (v);
}