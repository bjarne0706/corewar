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

void				validate_size_and_comment(int fd)
{
	unsigned int	size;
	char			comment[COMMENT_LENGTH];
	unsigned int	null_check;

	size = 0;
	if (read(fd, &size, 4) < 4)
		vm_error("Invalid file (exec code size)");
		printf("> size: %d\n", size);		//
	if (read(fd, &comment, COMMENT_LENGTH) < COMMENT_LENGTH)
		vm_error("Invalid file (comment)");
		printf("> comment: %s\n", comment);	
	null_check = 0;
	if ((read(fd, &null_check, 4) < 4) || null_check != 0)
		vm_error("Invalid file (NULL-delimiter)");
}
t_bool				parse_name(int fd, t_champ *ch)
{
	unsigned int	null_check;

	if (read(fd, &ch->name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (false);
		printf("> name: %s\n", ch->name);		//
	null_check = 0;
	if ((read(fd, &null_check, 4) < 4) || null_check != 0)
		return (false);
		printf("null: %#x\n", null_check);	//
	return (true);

}

t_bool				validate_magic(int fd)
{
	unsigned int	exec_magic;

	exec_magic = 0;
	if (read(fd, &exec_magic, 4) < 4)
		return (false);
	exec_magic = reverse_byte(exec_magic);
		printf("magic is: %x\n must be: %x\n", exec_magic, COREWAR_EXEC_MAGIC);	//
	return (exec_magic == COREWAR_EXEC_MAGIC);
}

void				parse_champ(t_vm *v, char *filecor, int n)
{
	int				fd;

	if ((fd = open(filecor, O_RDONLY)) < 0)
		vm_error("Can't open this rubbish");
	if (!validate_magic(fd))
		vm_error("Invalid file (magic header)");
		else printf("	Valid magic header!\n");		//
	if (++v->champs_num > MAX_PLAYERS)
		vm_error("Too many guys for such a tiny, tight VM!");
	v->champs[v->champs_num - 1] = add_champ(n);
	if (!parse_name(fd, v->champs[v->champs_num - 1]))
		vm_error("Invalid file (champion name)");
	validate_size_and_comment(fd);
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
		if (n < 1 || n > MAX_PLAYERS || !cor_filename(av[*i + 2]))
			print_usage();
		if (find_champ(v, n))
			vm_error("Players with the same id numbers");
		parse_champ(v, av[*i + 2], n);
		*i += 2;
	}
	else
		print_usage();
}