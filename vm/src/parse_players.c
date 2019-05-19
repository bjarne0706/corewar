/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_palyers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:53:35 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/18 14:53:37 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

t_bool				validate_magic(int fd)
{
	unsigned int	exec_magic;

	read(fd, &exec_magic, 4);
	exec_magic = reverse_byte(exec_magic);
		printf("magic: %x\nmustbe: %x\n", exec_magic, COREWAR_EXEC_MAGIC);	//
	if (exec_magic == COREWAR_EXEC_MAGIC)
		return (true);
	else
		return (false);
}

void				parse_champ(t_vm *v, char *filecor)
{
	int			fd;

	if ((fd = open(filecor, O_RDONLY)) < 0)
		vm_error("Can't open this rubbish");
	if (!validate_magic(fd))
		vm_error("Invalid file (magic header)");
	(void)v;	//

}

t_bool				cor_filename(const char *s)
{
	char	*p;

	p = NULL;
	if (s && (p = ft_strstr(s, ".cor")) && (ft_strlen(p) == 4) &&
		(ft_strlen(s) > 4))
		return (true);
	else
		return (false);
}

t_bool				find_champ(t_vm *v, int n)
{
	int		i;
	
	i = 0;
	while (i < MAX_PLAYERS)
	{
		while (!v->champs[i] && (i < MAX_PLAYERS))
			i++;
		if (i >= MAX_PLAYERS)
			break ;
		if (v->champs[i]->num == n)
			return (true);
		i++;
	}
	return (false);
}

void			flag_n(char *av[], int ac, int *i, t_vm *v)
{
	int			n;
	
	n = 0;
	if ((*i + 2 < ac) && ft_isint(av[*i + 1]))
	{
		n = ft_atoi(av[*i + 1]);
		if (n < 1 || n > MAX_PLAYERS || find_champ(v, n) ||
				!cor_filename(av[*i + 2]))
			print_usage();
		parse_champ(v, av[*i + 2]);
		v->champs_num++;
		*i += 2;
	}
	else
		print_usage();
}