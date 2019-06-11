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
	int		status;
	int		if_read;

	status = 1;
	if_read = 1;
	while (get_next_line(g_files->f_fd, &line) > 0)
	{
		if (find_op(line) == 1)
			make_lbl(line);
		else if (if_has_smthng(line))
			create_token(line);
		printf("LINE IN READ_ASM_AND_PUT_EXEC_COXE: %s\n", line);
		free(line);
		// if (line[0] !='\n' && line[0] != '#' && check_line(line))
		// {
		// 	if_read = disassemble_line(line);
		// 	// printf("LINE: %s STATUS: %d, IF_READ: %d\n", line, status, if_read);
		// }
	}
	// create_token();
	put_hex(g_exec_size, 4);
}

void		make_lbl(char *str)
{
	t_label		*tmp;
	t_label		*new;

	new = (t_label *)ft_memalloc(sizeof(t_label));
	new->mem_pos = g_exec_size;
	new->label = ft_strsub(str, 0, label_char_pos(str));
	// printf("label: %s\n", new->label);
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

void		make_op(char *str)
{
	t_oken	*tmp;
	t_oken	*new;
	
	new = (t_oken *)ft_memalloc(sizeof(t_oken));
	if (g_tkns == NULL)
		g_tkns = new;
	else
	{
		tmp = g_tkns;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			disassemble_line(char *line)
{
	t_tmp		*tmp;
	t_tmp		*new;
	// static int	flag = 0;

	new = (t_tmp *)ft_memalloc(sizeof(t_tmp));
	if (find_op(line) == 1)
	{
		new->label = ft_strsub(line, 0, label_char_pos(line));
		free(line);
		get_next_line(g_files->f_fd, &line);
		if (find_op(line) == 1)
		{
			new->op = NULL;
			return (0);
		}
		else
		{
			new->op = ft_strdup(line);
			free(line);
		}
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
		free(line);
	}
	if (g_tmp_op == NULL)
		g_tmp_op = new;
	else
	{
		tmp = g_tmp_op;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void		create_token(char *line)
{
	int 	type_of_op;

	printf("LINE IN CRATE_TOKEN: %s\n", line);
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
	new->code_types = ft_memalloc(8);
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
		// tmp->args[y] = ft_strdup(arr[y]);
		new->token->argums[y] = get_value_of_arg(arr[y], new, new->code_types);
		fill_type_code(new->code_types);
		y++;
	}
	num = 1;
}
// Надо сделать обработку меток, доделать их реализацию
//  и убрать обработку в процессе считывания