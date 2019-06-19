/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:22:04 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/22 15:22:06 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		read_asm_put_code_size(void)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

	while (get_next_line(g_files->f_fd, &line) > 0)
	{
		if (!comment_line(line))
		{
			if (ft_strchr(line, '#') || ft_strchr(line, ';'))
				del_comment(&line);
			del_space_end(&line);
			// printf("find_op: %d in line: %s\n", find_op(line), line);
			if (find_op(line) == 1)
				make_lbl(line);
			else if (if_has_smthng(line))
			{
					if (find_op(line) == 0)
					{f
						error("Syntax error.");

					}
					else if (find_op(line) == 3)
					{
						tmp = ft_strsub(line, 0, label_char_pos(line));
						tmp2 = ft_strsub(line, label_char_pos(line) + 1, ft_strlen(line) - (label_char_pos(line) + 1));
						make_lbl(tmp);
						create_token(tmp2);
						free(tmp);
						free(tmp2);
					}
					else
						create_token(line);					
			}
		}
		
		free(line);
	}
	if (g_tkns == NULL)
		error("Error: no operations");
	// t_label *tmp;

	// tmp = g_lbl;
	// while (tmp != NULL)
	// {
	// 	printf("FUCKING LABEL: %s\n", tmp->label);
	// 	tmp = tmp->next;
	// }
	put_hex(g_exec_size, 4);
	g_full_line = (unsigned char *)realloc(g_full_line,
	 PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + g_exec_size + 1);
}

int			comment_line(char *line)
{
	int		abc_flag;
	int		i;

	i = 0;
	abc_flag = 0;
	while (line[i])
	{
		if (ft_isalnum(line[i]))
			abc_flag = 1;
		if ((line[i] == '#' || line[i] == '#') && abc_flag == 0)
			return (1);
		i++;
	}
	return (0);
}

void		del_space_end(char **line)
{
	int		i;

	i = ft_strlen((*line)) - 1;
	while (i > 0 && ft_space((*line)[i]) && (*line)[i] != LABEL_CHAR && (*line)[i] != DIRECT_CHAR)
		i--;
	i++;
	(*line)[i] = '\0';
}

void		del_comment(char **line)
{
	int		i;

	i = -1;
	while ((*line)[++i])
		if ((*line)[i] == '#' || (*line)[i] == ';')
			break ;
	i--;
	while (i > 0 && !ft_isalnum((*line)[i]) && (*line)[i] != LABEL_CHAR && (*line)[i] != DIRECT_CHAR)
		i--;
	i++;
	(*line)[i] = '\0';
}

void		make_lbl(char *str)
{
	t_label		*tmp;
	t_label		*new;
	int			i;

	i = label_char_pos(str);
	printf("line %s\n", str);
	new = (t_label *)ft_memalloc(sizeof(t_label));
	new->mem_pos = g_exec_size;
	new->label = ft_strsub(str, 0, label_char_pos(str));
	while (str[++i])
	{
		printf("str[i] %c\n", str[i]);
		if (!ft_space(str[i]))
			error("Syntax error.1");
	}
		
	if (g_lbl == NULL)
		g_lbl = new;
	else
	{
		tmp = g_lbl;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		create_token(char *line)
{
	int 	type_of_op;

	type_of_op = get_op_name(line);
	work_on_op(type_of_op, line);
}

void		work_on_op(int num, char *line)
{
	t_oken	*tmp1;
	t_oken	*new;

	new = (t_oken *)ft_memalloc(sizeof(t_oken));
	new->token = (t_op *)ft_memalloc(sizeof(t_op));
	fill_token(num, new);
	fill_args(num, line, new);
	if (g_tkns == NULL)
		g_tkns = new;
	else
	{
		tmp1 = g_tkns;
		while (tmp1->next != NULL)
			tmp1 = tmp1->next;
		tmp1->next = new;
	}
}

void		handle_args(char **arr, t_oken *new, int num)
{
	int		y;
	int		x;

	y = 0;
	while (arr[y])
	{
		del_space_end(&arr[y]);
		x = trim_space(0, arr[y]);
		// printf("ARGUMENT: %s.\n", arr[y]);
		if (arr[y][x] == 'r')
		{
			new->code_size++;
			g_exec_size++;
			new->args_type[y] = 1;
		}
		else if (arr[y][x] == '%')
		{
			new->code_size += g_op_tab[num].t_dir_size;
			g_exec_size += g_op_tab[num].t_dir_size;
			new->args_type[y] = 2;
		}
		else
		{
			new->code_size += 2;
			g_exec_size += 2;
			new->args_type[y] = 3;
		}
		if (!validate_arg(arr[y], new->args_type[y]))
			error("Error: syntax error in argument.");
		new->args_value[y] = ft_strdup(arr[y]);
		y++;
	}
	num = 1;
}

int			validate_arg(char *arg, int type)
{
	int		x;

	x = trim_space(0, arg);
	if (type == 1)
	{
		while (arg[++x])
			if (!ft_isdigit(arg[x]) && arg[x] != '-')
				return (0);
	}
	else if (type == 2 && arg[x + 1] == LABEL_CHAR)
	{
		x++;
		while (arg[++x])
			if (ft_strchr(LABEL_CHARS, arg[x]) == 0)
				return (0);
	}
	else if (type == 2 && arg[x + 1] != LABEL_CHAR)
	{
		while (arg[++x])
			if (!ft_isdigit(arg[x]) && arg[x] != '-')
				return (0);
	}
	else
	{
		while (arg[++x])
			if (ft_strchr(LABEL_CHARS, arg[x]) == 0)
				return (0);
	}
	
	return (1);
}
