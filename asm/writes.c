/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:15:45 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 14:15:47 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_header(void)
{
	unsigned	i;

	g_full_line = ft_memalloc(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	ft_memcpy(g_full_line, &i, 4);
	g_posit += 4;
}

int			write_name(char *line)
{
	int		flag;
	char	*tmp_name;
	int		i;
	int		j;

	j = 0;
	if (g_str->name != NULL)
		error("Error: too many names.");
	g_str->name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	tmp_name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	flag = 1;
	i = validate_name_cmd(line) + 1;
	if (line[i] == '\n')
		tmp_name[j++] = '\n';
	while (flag > 0 && line[i] != '"')
	{
		while (line[i] && line[i] != '"')
		{
			check_size(&tmp_name, j, 0);
			tmp_name[j++] = line[i++];
		}
		if (line[i] != '"')
		{
			check_size(&tmp_name, j, 0);
			tmp_name[j++] = '\n';
		}
		if (line[i] != '"')
		{
			ft_strdel(&line);
			flag = get_next_line(g_files->f_fd, &line);
			i = 0;
		}
	}
	while (line[++i] && line[i] != COMMENT_CHAR && line[i] != ';')
	{
		if (!ft_space(line[i]) && line[i] != '\0')
			error("Syntax error.");
	}
	if (flag <= 0)
		error("Error: no closing bracket.");
	ft_strdel(&line);
	ft_memcpy(g_str->name, tmp_name, PROG_NAME_LENGTH);
	free(tmp_name);
	return (1);
}

int			write_comment(char *line)
{
	int		flag;
	char	*tmp_name;
	int		i;
	int		j;

	j = 0;
	if (g_str->comment != NULL)
		error("Error: too many comments.");
	g_str->comment = (char *)ft_memalloc(COMMENT_LENGTH);
	tmp_name = (char *)ft_memalloc(COMMENT_LENGTH);
	flag = 1;
	i = validate_comment_cmd(line) + 1;
	if (line[i] == '\n')
		tmp_name[j++] = '\n';
	while (flag > 0 && line[i] != '"')
	{
		while (line[i] && line[i] != '"')
		{
			check_size(&tmp_name, j, 1);
			tmp_name[j++] = line[i++];
		}
		if (line[i] != '"')
		{
			check_size(&tmp_name, j, 1);
			tmp_name[j++] = '\n';
		}
		if (line[i] != '"')
		{
			ft_strdel(&line);
			flag = get_next_line(g_files->f_fd, &line);
			i = 0;
		}
	}
	while (line[++i] && line[i] != COMMENT_CHAR && line[i] != ';')
	{
		if (!ft_space(line[i]) && line[i] != '\0')
			error("Syntax error.");
	}
	if (flag <= 0)
		error("Error: no closing bracket.");
	ft_strdel(&line);
	ft_memcpy(g_str->comment, tmp_name, COMMENT_LENGTH);
	free(tmp_name);
	return (1);
}

void		check_size(char **str, int size, int type)
{
	if (type)
	{
		if (size >= COMMENT_LENGTH)
		{
			ft_strdel(str);
			error("Error: too long comment.");
		}
	}
	else
	{
		if (size >= PROG_NAME_LENGTH)
		{
			ft_strdel(str);
			error("Error: too long name.");
		}
	}
}

int			validate_name_cmd(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i] != NAME_CMD_STRING[0])
		if (!ft_space(str[i]))
			error("Syntax error in name command.");
	i--;
	while (str[++i] != '"' && !ft_space(str[i]) && str[i])
		if (str[i] != NAME_CMD_STRING[j++])
			error("Syntax error in name command.");
	while (str[i] != '"' && ft_space(str[i]) && str[i])
		i++;
	if (str[i] == '\0' || str[i] != '"')
		error("Syntax error in name command.");
	return (i);
}

int			validate_comment_cmd(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i] != COMMENT_CMD_STRING[0])
		if (!ft_space(str[i]))
			error("Syntax error in comment command.");
	i--;
	while (str[++i] != '"' && !ft_space(str[i]) && str[i])
		if (str[i] != COMMENT_CMD_STRING[j++])
			error("Syntax error in comment command.");
	while (str[i] != '"' && ft_space(str[i]) && str[i])
		i++;
	if (str[i] == '\0' || str[i] != '"')
		error("Syntax error in comment command.");
		// printf("i: %d\n", i);
	return (i);
}

void		put_hex(int32_t nbr, int size)
{
	unsigned int	tmp;
	int				i;
	unsigned int	max;
	char			*res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		tmp = max + nbr + 1;
	else
		tmp = nbr;
	res = (char *)malloc(size);
	i = size;
	while (--i >= 0)
	{
		res[i] = tmp % 256;
		tmp /= 256;
	}
	ft_memcpy(g_full_line + g_posit, res, size);
	g_posit += size;
	free(res);
}

void		print_args(t_oken *tkn)
{
	int		size;
	int		y;

	y = 0;
	while (y < tkn->token->arg_count)
	{
		if (tkn->args_type[y] == 1)
			size = 1;
		else if (tkn->args_type[y] == 2)
			size = tkn->token->t_dir_size;
		else if (tkn->args_type[y] == 4)
			size = 2;
		put_hex(tkn->token->argums[y], size);
		y++;
	}
}
