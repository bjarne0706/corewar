/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:55:32 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/13 19:55:34 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*get_name(char *name)
{
	char	*str;
	int		e_len;
	int		name_len;

	e_len = (int)ft_strlen(ft_strrchr(name, '.'));
	name_len = (int)ft_strlen(name) - e_len;
	str = ft_strsub(name, 0, name_len);
	str = ft_strjoin(str, ".cor");
	return (str);
}

int				main(int ac, char **av)
{
	char		*filename;
	char 		**arr;
	char		*line;

	g_files = (t_files *)ft_memalloc(sizeof(t_files));
	if (ac != 2) {
		error("Error: incorrect number of files");
	}
	arr = ft_strsplit(av[1], '.');
	if (ft_strcmp(arr[1], "s") != 0) {
		error("Error: incorrect file extension");
	}
	g_files->f_fd = open(av[1], O_RDONLY);
	filename = get_name(av[1]);
	g_files->s_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	write_header();
	while (get_next_line(g_files->f_fd, &line) > 0)
	{
		if (ft_strstr(line, ".name"))
			write_player_name(line);
		free(line);
	}
}

void			write_header()
{
	char		*tmp;
	long int	i;

	tmp = (char *)ft_memalloc(4);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	tmp = ft_memcpy(tmp, &i, 4);
	write(g_files->s_fd, tmp, 4);
}

void				write_player_name(char *line)
{
	int 	brack_flag;
	char 	*name;
	char 	*tmp_name;

	name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	tmp_name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if (ft_strchr(line, '"'))
			brack_flag++;
		if (ft_strrchr(ft_strchr(line, '"'), '"'))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		get_next_line(g_files->f_fd, &line);
		if (brack_flag != 2)
			tmp_name = ft_strjoin(tmp_name, line);
//		printf("%s\n", line);
	}
		printf("%s\n", tmp_name);
	name = ft_memcpy(name, &tmp_name, 128);
	write(g_files->s_fd, name, 128);
}

unsigned int	reverse_byte(unsigned int num)
{
	unsigned   write;
	unsigned   bt;
	int     i;

	i = -1;
	write = 0;
	while (++i < 4)
	{
		bt = (num >> 8 * i) & 0xff;
		write |= bt << (24 - 8 * i);
	}
	return (write);
}

void			error(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
	exit(1);
}
