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
	ft_printf("	{yellow}./corewar [-d N -s N] [-v] [-n N]");
	ft_printf(" champ1.cor [-n N] champ2.cor <...>{-}\n");
	ft_printf("\n{u}{b}FLAGS:\n{0}");
	ft_printf("	{b}-d N{0}	: Dumps memory after N cycles then exits\n");
	ft_printf("	{b}-s N{0}	: Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("	{b}-v{0}	: Visual mode\n");
	ft_printf("	{b}-n N{0}	: Specifies player's number\n");
	exit(0);
}

void			flag_d(char *av[], int ac, int *i, t_vm *v)
{
	if (!v->options[0] && (*i + 1 < ac) && ft_isint(av[*i + 1]))
	{
		v->dump_cycles[0] = ft_atoi(av[*i + 1]);
		if (v->dump_cycles[0] < 0)
			v->dump_cycles[0] = -1;
		else
			v->options[0] = 'd';
		*i += 1;
	}
	else
		print_usage();
	
}

void			flag_s(char *av[], int ac, int *i, t_vm *v)
{
	if (!v->options[1] && (*i + 1 < ac) && ft_isint(av[*i + 1]))
	{
		v->dump_cycles[1] = ft_atoi(av[*i + 1]);
		if (v->dump_cycles[1] < 0)
			v->dump_cycles[1] = -1;
		else
			v->options[1] = 's';
		*i += 1;
	}
	else
		print_usage();
	
}

void			parse_args(int ac, char *av[], t_vm *v)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-d"))
			flag_d(av, ac, &i, v);
		else if (!ft_strcmp(av[i], "-s"))
			flag_s(av, ac, &i, v);
/*		else if (!ft_strcmp(av[i], "-v"))
			flag_v();
		else if (!ft_strcmp(av[i], "-n"))
			flag_n();
*/		
		i++;
	}
}

int				main(int ac, char *av[])
{
	t_vm		*v;

	errno = 0;
	if (ac > 1)
	{
		v = init_vm();
		parse_args(ac, av, v);
			printf("dump_cycles: %d||%d\nO: %s\n", v->dump_cycles[0], v->dump_cycles[1], v->options);	//
	}
	else
		print_usage();
	return (0);
}
