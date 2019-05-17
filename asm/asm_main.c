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
			write_name(line);
//		else if (ft_strstr(line, ".comment"))
//			write_comment(line);
		else
			write_token();
		free(line);
	}
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

void			write_header()
{
	char		*tmp;
	long int	i;

	tmp = (char *)ft_memalloc(4);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	tmp = ft_memcpy(tmp, &i, 4);
	write(g_files->s_fd, tmp, 4);
}

void			write_name(char *line)
{
	int 		brack_flag;
	char 		*name;
	char 		*tmp_name;
	long int	num;
	int 		i;

	i = 0;
	num = PROG_NAME_LENGTH;
	name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	name = ft_memcpy(name, tmp_name, num);
	write(g_files->s_fd, name, num);
//	write_exec_code_size();
}

void			write_comment(char *line)
{
	int 		brack_flag;
	char 		*name;
	char 		*tmp_name;
	long int	num;
	int 		i;

	i = 0;
	num = COMMENT_LENGTH;
	name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	name = ft_memcpy(name, tmp_name, num);
	write(g_files->s_fd, name, num);
//	write(g_files->s_fd, 0, 4);
}

void			write_token()
{
//	long str;
//	long str3;
	char *str4;
	char *str2;

	str2 = ft_memalloc(1);

//	str = 104;
//	str3 = 0x0b;
	str4 = NULL;
//	str = str & 0xff;
//	printf("%s\n", ft_itoa_base(str, 16));
//	str = ft_itoa_base(str, 16);
//	str2 = ft_memcpy(str2, &str, 1);
//	write(g_files->s_fd, str2, 1);
	str2 = ft_memcpy(str2, &str4, 1);
	write(g_files->s_fd, str2, 1);
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

int 			search_bracks(char *line)
{
	int 		i;

	i = -1;
	while (line[++i])
		if (line[i] == '"')
			return (i);
	return (0);
}

int 			search_r_bracks(char *line, int num)
{
	int 		i;

	i = ft_strlen(line);
	while (line[--i])
		if (line[i] == '"' && i != num)
			return (i);
	return (0);
}

void			write_exec_code_size()
{
	char		*code;
	long int	num;
	code = ft_memalloc(4);
	num = 256;
	code = ft_memcpy(code, &num, 4);
	write(g_files->s_fd, code, 4);
}

char 			*read_betw_brack(char *str)
{
	char	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new = (char *)ft_memalloc(PROG_NAME_LENGTH);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"' && str[i])
	{
		new[y] = str[i];
		y++;
		i++;
	}
	new[y] = '\0';
	free(str);
	return (new);
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
