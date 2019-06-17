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

void			write_header()
{
	unsigned	i;
	
	g_full_line = ft_memalloc(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	ft_memcpy(g_full_line, &i, 4);
	g_posit += 4;
}

int				write_name(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	char 		*tmp;
	long int	num;
	int 		i;

	i = 0;
	if (g_str->name_flag)
		error("Error: too many names.");
	num = PROG_NAME_LENGTH;
	g_str->name = (char *)ft_memalloc(num + 1);
	tmp_name = (char *)ft_memalloc(num + 1);
	brack_flag = 0;
	validate_name_comment_cmd(line, 1);
	while (brack_flag != 2)
	{
		tmp = ft_strdup(tmp_name);
		if (brack_flag != 1 && (i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i) || line[0] == '"')
			brack_flag++;
		free(tmp_name);
		tmp_name = ft_strjoin_three(tmp, line, "\n", 1);
		free(tmp);
		if (brack_flag != 2)
		{
			ft_strdel(&line);
			get_next_line(g_files->f_fd, &line);
		}
		if ((find_op(line) != 0 && brack_flag == 1) || ft_strstr(line, COMMENT_CMD_STRING))
			error("Error: no closing bracket.");
	}
	g_str->name_flag = 1;
	ft_strdel(&line);
	tmp_name = read_betw_brack(tmp_name, 1);
	ft_memcpy(g_str->name, tmp_name, num);
	free(tmp_name);
	return (1);
}

int				write_comment(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	char 		*tmp;
	long int	num;
	int 		i;

	i = 0;
	if (g_str->comment_flag)
		error("Error: too many comments.");
	num = COMMENT_LENGTH;
	g_str->comment = (char *)ft_memalloc(num * 2);
	tmp_name = (char *)ft_memalloc(num * 2);
	brack_flag = 0;
	validate_name_comment_cmd(line, 0);
	while (brack_flag != 2)
	{
		tmp = ft_strdup(tmp_name);
		if (brack_flag != 1 && (i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i) || line[0] == '"')
			brack_flag++;
		free(tmp_name);
		tmp_name = ft_strjoin_three(tmp, line, "\n", 0);
		free(tmp);
		if (brack_flag != 2)
		{
			ft_strdel(&line);
			get_next_line(g_files->f_fd, &line);
		}
		if ((find_op(line) != 0 && brack_flag == 1) || ft_strstr(line, NAME_CMD_STRING))
			error("Error: no closing bracket.");
	}
	g_str->comment_flag = 1;
	ft_strdel(&line);
	// printf("comment: %s\n", tmp_name);
	tmp_name = read_betw_brack(tmp_name, 0);
	// printf("comment: %s\n", tmp_name);
	ft_memcpy(g_str->comment, tmp_name, num);
	if (ft_strlen(tmp_name) > COMMENT_LENGTH)
		error("Error: too long comment.");
	free(tmp_name);
	return (1);
}

void		validate_name_comment_cmd(char *str, int n_or_c)
{
	int		i;
	char	*pattern;
	char	*error_msg;

	if (n_or_c)
	{
		error_msg = "Syntax error in name command.";
		pattern = ft_strdup(NAME_CMD_STRING);
	}
	else
	{
		error_msg = "Syntax error in comment command.";
		pattern = ft_strdup(COMMENT_CMD_STRING);
	}
	printf("pattern: %s\n", pattern);
	i = -1;
	while (str[++i] != '"' && !ft_space(str[i]) && str[i])
		if (str[i] != pattern[i])
			error(error_msg);
	while (str[i] != '"' && ft_space(str[i]) && str[i])
		i++;
	if (str[i] == '\0' || str[i] != '"')
		error(error_msg);
	free(pattern);
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
		else if (tkn->args_type[y] == 3)
			size = 2;
		put_hex(tkn->token->argums[y], size);
		y++;
	}
}