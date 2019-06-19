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
/*
Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>
    -a        : Prints output from "aff" (Default is to hide it)
#### TEXT OUTPUT MODE ##########################################################
    -d N      : Dumps memory after N cycles then exits
    -s N      : Runs N cycles, dumps memory, pauses, then repeats
    -v N      : Verbosity levels, can be added together to enable several
                - 0 : Show only essentials
                - 1 : Show lives
                - 2 : Show cycles
                - 4 : Show operations (Params are NOT litteral ...)
                - 8 : Show deaths
                - 16 : Show PC movements (Except for jumps)
#### BINARY OUTPUT MODE ########################################################
    -b        : Binary output mode for corewar.42.fr
    --stealth : Hides the real contents of the memory
#### NCURSES OUTPUT MODE #######################################################
    -n        : Ncurses output mode
    --stealth : Hides the real contents of the memory
################################################################################
*/

int				main(int ac, char *av[])
{
	t_vm		*v;

	errno = 0;
	if (ac > 1)
	{
		v = init_vm();
		parse_args(ac, av, v);
		if (v->champs_num < 1)
			vm_error("Where are these little naughty players?");
		assign_champ_nums(v);
//			print_champs(v);		//
		setup_arena(v);
			print_arena(v, v->options[0]);		//
			print_color_map(v);		///
		introduce_champs(v);		//
		setup_carriages(v);
//					print_carriages(v);		//
		// while (v->cycles < 2000)			////
			// run_cycle(v);
//			print_vm_params(v);		//
		run_the_game(v);
//			print_arena(v, v->options[0]);		//
//			print_color_map(v);		///
		hail_the_hero(v);
			// print_carriages(v);		//
//			print_arena(v, v->options[0]);		//
	}
	else
		print_usage();
//		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
//		system("leaks -q corewar");	//
	return (0);
}
