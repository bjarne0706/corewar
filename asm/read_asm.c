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
	long	num;

	while (get_next_line(g_files->f_fd, &line) > 0)
	{
		if (line[0] !='\n' && line[0] != '#' && check_line(line))
			disassemble_line(line);
	}
	create_token();
	put_hex(g_exec_size, 4);
}

void		disassemble_line(char *line)
{
	t_tmp	*tmp;
	t_tmp	*new;

	new = (t_tmp *)ft_memalloc(sizeof(t_tmp));
	if (g_tmp_op == NULL)
		g_tmp_op = new;
	else
	{
		tmp = g_tmp_op;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (find_op(line) == 1)
	{
		new->label = ft_strsub(line, 0, label_char_pos(line));
		free(line);
		get_next_line(g_files->f_fd, &line);
		if (find_op(line) == 1)
			disassemble_line(line);
		new->op = ft_strdup(line);
		free(line);
	}
	else if (find_op(line) == 2)
	{
		new->label = NULL;
		new->op = ft_strdup(line);
		free(line);
	}
	else if (find_op(line) == 3)
	{
		new->label = ft_strsub(line, 0, label_char_pos(line));
		new->op = ft_strsub(line, label_char_pos(line) + 1, ft_strlen(line) - 1);
	}
}

void		create_token()
{
	int 	type_of_op;
	t_tmp	*tmp;

	tmp = g_tmp_op;
	while (tmp != NULL)
	{
		type_of_op = get_op_name(tmp->op);
		work_on_op(type_of_op, tmp);
		tmp = tmp->next;
	}
}

void		work_on_op(int num, t_tmp *tmp)
{
	t_oken	*tmp1;
	t_oken	*new;

	new = (t_oken *)ft_memalloc(sizeof(t_oken));
	new->token = (t_op *)ft_memalloc(sizeof(t_op));
	if (tmp->label)
		new->label = ft_strdup(tmp->label);
	fill_token(num, new);
	fill_args(num, tmp, new);
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

void		handle_args(char **arr, t_oken *new, int num, t_tmp *tmp)
{
	int		y;
	int		x;

	y = 0;
	tmp->args = (char **)ft_memalloc(sizeof(char *) * 3);
	while (arr[y])
	{
		x = trim_space(0, arr[y]);
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
		tmp->args[y] = ft_strdup(arr[y]);
		y++;
	}
	num = 1;
}
