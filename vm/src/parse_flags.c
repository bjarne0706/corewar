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

void			flag_v(t_vm *v)
{
	if (!v->options[2])
		v->options[2] = 'v';
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
		else if (!ft_strcmp(av[i], "-v"))
			flag_v(v);
		else if (!ft_strcmp(av[i], "-n"))
			flag_n(av, ac, &i, v);
		else if (cor_filename(av[i]))
			parse_champ(v, av[i], 0);
		else
			print_usage();
		i++;
	}
}