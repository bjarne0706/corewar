/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:26:20 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/28 17:26:24 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			die_check(t_vm *v)
{
	int		i;
	
	v->checks_done++;
	kill_those_loosers(v);
	if (v->checks_done == MAX_CHECKS || v->lives_since_check >= NBR_LIVE)
	{
		v->cyc_to_die -= CYCLE_DELTA;
		v->checks_done = 0;
	}
	v->cyc_since_check = 0;
	i = 0;
	while (i < v->champs_num)
	{
		v->champs[i]->prev_lives = v->champs[i]->current_lives;
		v->champs[i]->current_lives = 0;
		i++;
	}
	v->lives_since_check = 0;
}

void			run_the_game(t_vm *v)
{
	while (v->carrs_num > 0)
	{
		run_cycle(v);
		if (v->cyc_since_check == v->cyc_to_die || v->cyc_to_die <= 0)
			die_check(v);
	}
}
