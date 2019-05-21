#include "asm.h"
#include "../op.c"

void		read_asm_put_code_size(void)
{
	char	*line;

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
	// t_oken *tmp2;

	// tmp2 = g_tkns;
	// while (tmp2 != NULL)
	// {
	// 	if (tmp2->label)
	// 		printf("Label: %s\n", tmp2->label);
	// 	printf("name: %s\n", tmp2->token->name);
	// 	printf("code: %lx\n", tmp2->token->code);
	// 	printf("arg_count: %ld\n", tmp2->token->arg_count);
	// 	printf("cycles: %ld\n", tmp2->token->cycles);
	// 	printf("arg_code_type: %d\n", tmp2->token->arg_code_type);
	// 	printf("dir_size: %d\n\n", tmp2->token->t_dir_size);
	// 	tmp2 = tmp2->next;
	// }
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
		new->label = ft_strdup(line);
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
	tkn->token->name = op_tab[num].name;
	tkn->token->code = op_tab[num].code;
	tkn->token->arg_count = op_tab[num].arg_count;
	tkn->token->cycles = op_tab[num].cycles;
	tkn->token->arg_code_type = op_tab[num].arg_code_type;
	tkn->token->t_dir_size = op_tab[num].t_dir_size;
}

void		fill_args(int num, char *tmp, t_oken *new)
{
	
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
	while (line[i] && line[i] != 'r' && line[i] != '%' && line[i] != ' ')
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
//void		create_token(void)
//{
//
//}
