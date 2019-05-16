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
			write_name(line);
		else if (ft_strstr(line, ".comment"))
			write_comment(line);
		else
			write_token();
		free(line);
	}
}

void			write_token()
{

}

void			write_name(char *line)// 1->name    0->comment
{
	int 		brack_flag;
	char 		*name;
	char 		*tmp_name;
	long int	num;

	num = PROG_NAME_LENGTH;
	name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if (ft_strchr(line, '"'))
			brack_flag++;
		if (ft_strrchr(line, '"'))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	name = ft_memcpy(name, tmp_name, num);
	write(g_files->s_fd, name, num);
//	write(g_files->s_fd, 0, 4);
	//	write_exec_code_size();
}

void			write_comment(char *line)
{
	int 		brack_flag;
	char 		*name;
	char 		*tmp_name;
	long int	num;

	num = COMMENT_LENGTH;
	name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if (ft_strchr(line, '"'))
			brack_flag++;
		if (ft_strrchr(line, '"'))
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

void			write_header()
{
	char		*tmp;
	long int	i;

	tmp = (char *)ft_memalloc(4);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	tmp = ft_memcpy(tmp, &i, 4);
	write(g_files->s_fd, tmp, 4);
}

void			write_exec_code_size()
{
	char		*code;
	long int	num;
	code = ft_memalloc(4);
	num = CHAMP_MAX_SIZE;
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
