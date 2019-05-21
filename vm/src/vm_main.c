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

void			print_usage(void)
{
	ft_printf("{b}{yellow}{u}USAGE:{0}\n");
	ft_printf("	{yellow}./corewar [-d N -s N] [-v] <[-n N]");
	ft_printf(" champ1.cor> <[-n N] champ2.cor> <...>{-}\n");
	ft_printf("\n{u}{b}FLAGS:\n{0}");
	ft_printf("	{b}-d N{0}	: Dumps memory after N cycles then exits\n");
	ft_printf("	{b}-s N{0}	: Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("	{b}-v{0}	: Visual mode\n");
	ft_printf("	{b}-n N{0}	: Specifies player's number ");
	ft_printf("(0 < N <= number_of_players (%d max))\n", MAX_PLAYERS);
//		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
//		system("leaks -q corewar");		//
	exit(1);
}

int				main(int ac, char *av[])
{
	t_vm		*v;

	errno = 0;
	if (ac > 1)
	{
		v = init_vm();
		parse_args(ac, av, v);
			printf("> Options: ");		//
			for (size_t i = 0; i < ft_strlen(v->options); i++)	//
					printf("%c]", v->options[i]);		///
			printf("\n> dump_cycles: %d||%d\n", v->dump_cycles[0], v->dump_cycles[1]);	//
			printf("How many champs? %d\n", v->champs_num);	//
		if (v->champs_num < 1)
			vm_error("Where are these little naughty players?");
		assign_champ_nums(v);
			print_champs(v);		//

	}
	else
		print_usage();
//		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
//		system("leaks -q corewar");	//
	return (0);
}
