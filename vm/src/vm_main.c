/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:29:59 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/16 15:30:00 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int				main(int ac, char *av[])
{
	t_vm		*v;

	errno = 0;
	if (ac > 1)
	{
		v = init_vm();
		parse_vm_args(ac, av, v);
		if (v->champs_num < 1)
			vm_error("Where are these little naughty players?");
		update_options(v);
		assign_champ_nums(v);
		setup_arena(v);
		if (!v->options[2])
			introduce_champs(v);
		setup_carriages(v);
		run_the_game(v);
		if (!v->options[2] && v->options[4])
			v->options[4] == 'E' ? print_arena(v, 'D') : print_arena(v, 'd');
		hail_the_hero(v);
		byebye_our_darling(v);
	}
	else
		print_usage();
	return (0);
}
