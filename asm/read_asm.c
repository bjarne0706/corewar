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
		// printf("start line:%s\n", line);
		if (line[0] !='\n' && line[0] != '#' && check_line(line))
		{
			disassemble_line(line);
			// printf("Approved line:%s\n", line);
		}
	}
	create_token();
	hex_con(g_exec_size, 4);
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
		if (str[i + 1] == LABEL_CHAR && str[i] == DIRECT_CHAR)
		{
			// printf("1:%c\n", str[i]);
			i += 2;
			while (str[i] != SEPARATOR_CHAR)
			{
				if (!ft_strchr(LABEL_CHARS, str[i]))
					return (0);
				i++;
			}
				
		}
		if (str[i] != ' ' && str[i] != '\t' && str[i] != SEPARATOR_CHAR &&
		  str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR && !ft_isalnum(str[i]) && str[i] != '-')
			return (0);
		// printf("2:%c\n", str[i]);
		i++;
	}
	return (1);
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
		printf("tmp op:%s\n", tmp->op);
		type_of_op = get_op_name(tmp->op);
		work_on_op(type_of_op, tmp);
		tmp = tmp->next;
		printf("\n");
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
	printf("num: %d\n", num);
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

void		fill_args(int num, t_tmp *tmp1, t_oken *new)
{
	char	*tmp;
	int		i;
	char	**arr;

	i = trim_space(0, tmp1->op);
	while (ft_isalpha(tmp1->op[i]))
		i++;
	tmp = &tmp1->op[i];
	arr = ft_strsplit(tmp, SEPARATOR_CHAR);
	// printf("arr[0]:%s\n", arr[0]);
	// if (arr[1])
	// 	printf("arr[1]:%s\n", arr[1]);
	// if (arr[2])
	// 	printf("arr[1]:%s\n", arr[2]);
	if (count_separ(tmp1->op) != new->token->arg_count - 1)
		error("Incorrect line");
	handle_args(arr, new, num, tmp1);
}

int			count_separ(char *str)
{
	int		i;
	int		counter;

	counter = 0;
	i = -1;
	printf("str:%s\n", str);
	while (str[++i])
	{
		if (str[i] == SEPARATOR_CHAR)
			counter++;
	}
	printf("counter: %d\n", counter);
	return (counter);
}

void		handle_args(char **arr, t_oken *new, int num, t_tmp *tmp)
{
	int		y;
	int		x;

	y = 0;
	tmp->args = (char **)ft_memalloc(sizeof(char *) * 3);
	printf("arr[y]: %s\n", arr[y]);
	while (arr[y])
	{
		x = trim_space(0, arr[y]);
		printf("%s", &arr[y][x]);
		if (arr[y][x] == 'r')
		{
			new->code_size++;
			g_exec_size++;
			new->args_type[y] = 1; // T_REG
		}
		else if (arr[y][x] == '%')
		{
			new->code_size += g_op_tab[num].t_dir_size;
			g_exec_size += g_op_tab[num].t_dir_size;
			new->args_type[y] = 2;//T_DIR
		}
		else
		{
			new->code_size += 2;
			g_exec_size += 2;
			new->args_type[y] = 3;//T_IND
		}
		tmp->args[y] = ft_strdup(arr[y]);
		printf("\narg:%s\n", tmp->args[y]);
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
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[0] != 'r' && line[i] != DIRECT_CHAR && line[i] != ' ' && line[i] != '\t')
	{
		name[y++] = line[i++];
		if (choose_name(name) > 0)
			op_type = choose_name(name);
	}
	free(name);
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
