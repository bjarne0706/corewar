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

int				main(int ac, char **av)
{
	char		*filename;
	char 		**arr;

	g_files = (t_files *)ft_memalloc(sizeof(t_files));
	g_str = (t_strings *)ft_memalloc(sizeof(t_strings));
	g_exec_size = 0;
	if (ac != 2)
		error("Error: incorrect number of files");
	arr = ft_strsplit(av[1], '.');
	if (ft_strcmp(arr[1], "s") != 0)
		error("Error: incorrect file extension");
	g_files->f_fd = open(av[1], O_RDONLY);
	filename = get_name(av[1]);
	g_files->s_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	write_header();
	write_all();
}

void			write_all(void)
{
	char	*line;
	long	str4;
	char	*str2;
	int 	num;

	num = 0;
	str4 = 0x0;
	str2 = ft_memalloc(4);
	while (get_next_line(g_files->f_fd, &line) > 0 && num != 2)
	{
		if (ft_strstr(line, ".name"))
			num += write_name(line);
		else if (ft_strstr(line, ".comment"))
			num += write_comment(line);
		free(line);
	}
	write(g_files->s_fd, g_str->name, PROG_NAME_LENGTH);
	str2 = ft_memcpy(str2, &str4, 4);
	write(g_files->s_fd, str2, 4);
	read_asm_put_code_size();
	write(g_files->s_fd, g_str->comment, COMMENT_LENGTH);
	write_token();
}

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

int		ft_abs(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

char	*ft_itoa_base(int value, int base)
{
	char	*str;
	int		size;
	char	*tab;
	int		flag;
	int		tmp;
	flag = 0;
	size = 0;
	tab = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (0);
	if (value < 0 && base == 10)
		flag = 1;
	tmp = value;
	while (tmp /= base)
		size++;
	size = size + flag + 1;
	str = (char *)malloc(sizeof(char) * size  + 1);
	str[size] = '\0';
	if (flag == 1)
		str[0] = '-';
	while (size > flag)
	{
		str[size - 1] = tab[ft_abs(value % base)];
		size--;
		value /=base;
	}
	return (str);
}
