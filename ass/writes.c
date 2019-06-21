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

int			write_name(char *line, int j, int i, int flag)
{
	char	*tmp_name;

	j = 0;
	if (g_str->name != NULL)
		error("Error: too many names.");
	g_str->name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	tmp_name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	flag = 1;
	i = validate_name_cmd(line) + 1;
	if (line[i] == '\n')
		tmp_name[j++] = '\n';
	write_name_p2(&i, &j, &line, &tmp_name);
	while (line[++i] && line[i] != COMMENT_CHAR && line[i] != ';')
		if (!ft_space(line[i]) && line[i] != '\0')
			error("Syntax error.");
	if (flag <= 0)
		error("Error: no closing bracket.");
	ft_strdel(&line);
	ft_memcpy(g_str->name, tmp_name, PROG_NAME_LENGTH);
	free(tmp_name);
	return (1);
}

int			write_comment(char *line, int j, int i, int flag)
{
	char	*tmp_name;

	if (g_str->comment != NULL)
		error("Error: too many comments.");
	g_str->comment = (char *)ft_memalloc(COMMENT_LENGTH);
	tmp_name = (char *)ft_memalloc(COMMENT_LENGTH);
	i = validate_comment_cmd(line) + 1;
	if (line[i] == '\n')
		tmp_name[j++] = '\n';
	write_comment_p2(&i, &j, &line, &tmp_name);
	while (line[++i] && line[i] != COMMENT_CHAR && line[i] != ';')
		if (!ft_space(line[i]) && line[i] != '\0')
			error("Syntax error.");
	if (flag <= 0)
		error("Error: no closing bracket.");
	ft_strdel(&line);
	ft_memcpy(g_str->comment, tmp_name, COMMENT_LENGTH);
	free(tmp_name);
	return (1);
}

void		write_comment_p2(int *i, int *j, char **line, char **tmp_name)
{
	int		flag;

	flag = 1;
	while (flag > 0 && (*line)[(*i)] != '"')
	{
		while ((*line)[(*i)] && (*line)[(*i)] != '"')
		{
			check_size(tmp_name, (*j), 1);
			(*tmp_name)[(*j)++] = (*line)[(*i)++];
		}
		if ((*line)[(*i)] != '"')
		{
			check_size(tmp_name, (*j), 1);
			(*tmp_name)[(*j)++] = '\n';
			ft_strdel(line);
			flag = get_next_line(g_files->f_fd, line);
			(*i) = 0;
		}
	}
}

void		write_name_p2(int *i, int *j, char **line, char **tmp_name)
{
	int		flag;

	flag = 1;
	while (flag > 0 && (*line)[(*i)] != '"')
	{
		while ((*line)[(*i)] && (*line)[(*i)] != '"')
		{
			check_size(tmp_name, (*j), 0);
			(*tmp_name)[(*j)++] = (*line)[(*i)++];
		}
		if ((*line)[(*i)] != '"')
		{
			check_size(tmp_name, (*j), 0);
			(*tmp_name)[(*j)++] = '\n';
			ft_strdel(line);
			flag = get_next_line(g_files->f_fd, line);
			(*i) = 0;
		}
	}
}
