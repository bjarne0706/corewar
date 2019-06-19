/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_op_and_fill_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:47:18 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/06 14:47:19 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		fill_token(int num, t_oken *tkn)
{
	tkn->mem_pos = g_exec_size;
	tkn->token->name = g_op_tab[num].name;
	g_exec_size++;
	tkn->code_size++;
	tkn->token->code = g_op_tab[num].code;
	tkn->token->arg_count = g_op_tab[num].arg_count;
	tkn->token->cycles = g_op_tab[num].cycles;
	tkn->token->arg_code_type = g_op_tab[num].arg_code_type;
	if (g_op_tab[num].arg_code_type)
	{
		g_exec_size++;
		tkn->code_size++;
	}
	tkn->token->t_dir_size = g_op_tab[num].t_dir_size;
}

void		fill_args(int num, char *line, t_oken *new)
{
	char	*tmp;
	int		i;
	char	**arr;

	i = trim_space(0, line);
	while (ft_isalnum(line[i]))
		i++;
	tmp = &line[i];
	// printf("LINE:%s\n", line);
	arr = ft_strsplit(tmp, SEPARATOR_CHAR);
	// i = 0;
	// while (i < new->token->arg_count)
	// {
	// 	printf("ARR IN FILL_ARGS: %s.\n", arr[i]);
	// 	i++;
	// }
	if (count_separ(line) != new->token->arg_count - 1)
		error("Incorrect line.");
	handle_args(arr, new, num);
	free_and_ret(arr);
}

int			if_has_smthng(char *line)
{
	int		i;
	int		sum;

	sum = 0;
	i = -1;
	while (line[++i])
		if (ft_isalnum(line[i]) || ft_strchr(LABEL_CHARS, line[i])
		 || line[i] == LABEL_CHAR || line[i] == DIRECT_CHAR
		  || line[i] == SEPARATOR_CHAR)
			sum++;
	if (sum == 0)
		return (0);
	return (1);
}

int			find_op(char *line)
{
	int		sum;
	int		i;
	int		y;
	int		tmp;

	tmp = 0;
	i = 0;
	y = 0;
	sum = 0;
	while (line[y] && !ft_space(line[y]))
	{
		if (y > 0)
			if (line[y] == LABEL_CHAR && ft_strchr(LABEL_CHARS, line[y - 1]))
			{
				sum++;
				break ;
			}
		if (ft_isalnum(line[y]) && ft_space(line[y + 1]))
		{
			y = 0;
			break ;
		}
		y++;
	}
	while (i < 16)
	{
		if (ft_strstr(&line[y], g_op_tab[i].name))
		{
			sum += 2;
			break ;
		}
		i++;
	}
	// printf("on line %s sum:%d\n",line, sum);
	return (sum);
}

int			get_op_name(char *line)
{
	int		i;
	int		start;
	int		y;
	char	*name;
	char	*tmp;
	
	name = (char *)ft_memalloc(6);
	i = 0;
	y = 0;
	if (line[i] == LABEL_CHAR)
		i++;
	while (ft_space(line[i]))
		i++;
	start = i;
	while (line[i] && line[0] != 'r' && line[i] != DIRECT_CHAR && !ft_space(line[i]))
	{
		y++;
		i++;
	}
	tmp = name;
	name = ft_strsub(line, start, y);
	free(tmp);
	free(name);
	if (!choose_name(name))
		error("Error: operation does not exist.");
	return (choose_name(name) - 1);
}

int			check_line(char *str)
{
	int		i;
	int		y;

	i = trim_space(0, str);
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_space(str[i]) && str[i] != SEPARATOR_CHAR &&
			str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR &&
			!ft_isalnum(str[i]) && str[i] != '-' &&
			!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
		i++;
	}
	return (1);
}