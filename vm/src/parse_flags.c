/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:59:18 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/18 12:59:21 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			flag_e(char *av[], int *i, t_vm *v)
{
	if (!ft_strcmp(av[*i], "-E"))
		v->options[4] = 'E';
	else
		v->options[4] = 'e';
}

void			flag_l(char *av[], int ac, int *i, t_vm *v)
{
	if ((*i + 1 < ac) && ft_isint(av[*i + 1]))
	{
		v->log = ft_atoi(av[*i + 1]);
		if (v->log < 0 || v->log > 31)
			print_usage();
		*i += 1;
	}
	else
		print_usage();
}

void			flag_d(char *av[], int ac, int *i, t_vm *v)
{
	if (!v->options[0] && (*i + 1 < ac) && ft_isint(av[*i + 1]))
	{
		v->dump_cycles[0] = ft_atoi(av[*i + 1]);
		if (v->dump_cycles[0] < 0)
			v->dump_cycles[0] = -1;
		else
		{
			if (!ft_strcmp(av[*i], "-D"))
				v->options[0] = 'D';
			else
				v->options[0] = 'd';
		}
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
		if (v->dump_cycles[1] <= 0)
			v->dump_cycles[1] = -1;
		else
		{
			if (!ft_strcmp(av[*i], "-S"))
				v->options[1] = 'S';
			else
				v->options[1] = 's';
		}
		*i += 1;
	}
	else
		print_usage();
}

void			parse_vm_args(int ac, char *av[], t_vm *v)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-D") || !ft_strcmp(av[i], "-d") ||
				!ft_strcmp(av[i], "-dump"))
			flag_d(av, ac, &i, v);
		else if (!ft_strcmp(av[i], "-S") || !ft_strcmp(av[i], "-s"))
			flag_s(av, ac, &i, v);
		else if (!ft_strcmp(av[i], "-E") || !ft_strcmp(av[i], "-e"))
			flag_e(av, &i, v);
		else if (!ft_strcmp(av[i], "-l"))
			flag_l(av, ac, &i, v);
		else if (!ft_strcmp(av[i], "-v"))
			v->options[2] = 'v';
		else if (!ft_strcmp(av[i], "-a"))
			v->options[3] = 'a';
		else if (!ft_strcmp(av[i], "-n"))
			flag_n(av, ac, &i, v);
		else if (cor_filename(av[i]))
			parse_champ(v, av[i], 0);
		else
			print_usage();
	}
}
