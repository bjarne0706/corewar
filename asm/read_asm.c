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
	char	*code;

	code = ft_memalloc(4);
	while (get_next_line(g_files->f_fd, &line) > 0)
	{
		if (line[0] !='\n')
			disassemble_line(line);
	}
	t_tmp *tmp;

	tmp = g_tmp_op;
	while (tmp != NULL)
	{
		if (tmp->label)
			printf("|%s\n", tmp->label);
		printf("%s|\n", tmp->op);
		tmp = tmp->next;
	}
	create_token();
	num = reverse_byte(g_exec_size & 0xff);
	code = ft_memcpy(code, &num, 4);
	write(g_files->s_fd, code, 4);
	printf("\n%ld\n", g_exec_size);
	t_oken *tmp2;

	tmp2 = g_tkns;
	while (tmp2 != NULL)
	{
		if (tmp2->label)
			printf("Label: %s\n", tmp2->label);
		printf("code_size: %d\n", tmp2->code_size);
		printf("mem_pos: %d\n", tmp2->mem_pos);
		printf("name: %s\n", tmp2->token->name);
		printf("code: %lx\n", tmp2->token->code);
		printf("arg_count: %ld\n", tmp2->token->arg_count);
		printf("cycles: %ld\n", tmp2->token->cycles);
		printf("arg_code_type: %d\n", tmp2->token->arg_code_type);
		printf("dir_size: %d\n\n", tmp2->token->t_dir_size);
		tmp2 = tmp2->next;
	}
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
	if (ft_strchr(line, LABEL_CHAR) != 0 && ft_strchr(line, DIRECT_CHAR) == 0)
	{
		new->label = ft_strsub(line, 0, ft_strlen(line) - 1);
		free(line);
		get_next_line(g_files->f_fd, &line);
		new->op = ft_strdup(line);
		free(line);
	}
	else
	{
		new->label = NULL;
		new->op = ft_strdup(line);
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
		new->label = tmp->label;
	fill_token(num, new);
	fill_args(num, tmp->op, new);
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

void		fill_token(int num, t_oken *tkn)
{
	tkn->mem_pos = g_exec_size;
	tkn->token->name = g_op_tab[num].name;
	g_exec_size++;												//cause of operation code
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
	tmp = ft_strchr(&line[i], ' ');
	arr = ft_strsplit(tmp, SEPARATOR_CHAR);
	// int kek = 0;
	// while (arr[kek])
	// {
	// 	printf("%d: |%s|\n", kek + 1, arr[kek]);
	// 	kek++;
	// }
	printf("%s\n", tmp);
	handle_args(arr, new, num);
}

void		handle_args(char **arr, t_oken *new, int num)
{
	int		y;
	int		x;

	y = 0;
	while (arr[y])
	{
		x = trim_space(0, arr[y]);
		if (arr[y][x] == 'r')
		{
			new->code_size++;
		g_exec_size++;

		}
		else if (arr[y][x] == '%')
		{
			new->code_size += g_op_tab[num].t_dir_size;
			g_exec_size += g_op_tab[num].t_dir_size;

		}
		else
		{
			new->code_size += 2;
			g_exec_size += 2;
		}
			// if (arr[y][x])
		y++;
	}
	num = 1;
}

int			trim_space(int i, char *line)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int			get_op_name(char *line)
{
	int		i;
	int		y;
	char	*name;
	int 	op_type;

	op_type = 0;
	name = (char *)ft_memalloc(6);
	i = 0;
	y = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != 'r' && line[i] != DIRECT_CHAR && line[i] != ' ')
	{
		name[y++] = line[i++];
		if (choose_name(name) > 0)
			op_type = choose_name(name);
	}
//	printf("1: %s\n", name);
//	printf("type: %d\n", op_type);
	return (op_type - 1);
}

int 		choose_name(char *line)
{
	if (ft_strcmp(line, "live") == 0)
		return (1);
	else if (ft_strcmp(line, "ld") == 0)
		return (2);
	else if (ft_strcmp(line, "st") == 0)
		return (3);
	else if (ft_strcmp(line, "add") == 0)
		return (4);
	else if (ft_strcmp(line, "sub") == 0)
		return (5);
	else if (ft_strcmp(line, "and") == 0)
		return (6);
	else if (ft_strcmp(line, "or") == 0)
		return (7);
	else if (ft_strcmp(line, "xor") == 0)
		return (8);
	else if (ft_strcmp(line, "zjmp") == 0)
		return (9);
	else if (ft_strcmp(line, "ldi") == 0)
		return (10);
	else if (ft_strcmp(line, "sti") == 0)
		return (11);
	else if (ft_strcmp(line, "fork") == 0)
		return (12);
	else if (ft_strcmp(line, "lld") == 0)
		return (13);
	else if (ft_strcmp(line, "lldi") == 0)
		return (14);
	else if (ft_strcmp(line, "lfork") == 0)
		return (15);
	else if (ft_strcmp(line, "aff") == 0)
		return (16);
	else
		return (0);
}
