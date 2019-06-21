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

void		read_asm_put_code_size(char *line)
{
	char	*tmp;
	char	*tmp2;
	int		r;

	r = 1;
	tmp = NULL;
	tmp2 = NULL;
	if (!if_has_smthng(line) && line[0] != '\0')
		g_new_l = 1;
	while (r > 0)
	{
		read_asm_p2(line, tmp, tmp2);
		if (!if_has_smthng(line) && line[0] != '\0')
			g_new_l = 1;
		free(line);
		r = get_next_line(g_files->f_fd, &line);
	}
	if (g_tkns == NULL)
		error("Error: no operations");
	put_hex(g_exec_size, 4);
	g_full_line = (unsigned char *)realloc(g_full_line,
		PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + g_exec_size + 1);
}

void		read_asm_p2(char *line, char *tmp, char *tmp2)
{
	if (!comment_line(line))
	{
		if (ft_strchr(line, '#') || ft_strchr(line, ';'))
			del_comment(&line);
		del_space_end(&line);
		if (find_op(line, 0, 0, 0) == 1)
			make_lbl(line);
		else if (if_has_smthng(line))
		{
			if (find_op(line, 0, 0, 0) == 0)
				error("Syntax error.");
			else if (find_op(line, 0, 0, 0) == 3)
			{
				tmp = ft_strsub(line, 0, label_char_pos(line));
				tmp2 = ft_strsub(line, label_char_pos(line) + 1,
						ft_strlen(line) - (label_char_pos(line) + 1));
				make_lbl(tmp);
				create_token(tmp2);
				free(tmp);
				free(tmp2);
			}
			else
				create_token(line);
		}
	}
}

void		make_lbl(char *str)
{
	t_label		*tmp;
	t_label		*new;
	int			i;

	new = (t_label *)ft_memalloc(sizeof(t_label));
	new->mem_pos = g_exec_size;
	new->label = ft_strsub(str, 0, label_char_pos(str));
	i = label_char_pos(str) - 1;
	check_labels_chars(new->label);
	while (str[++i] && i != (int)ft_strlen(str))
		if (!ft_space(str[i]) && str[i] != LABEL_CHAR)
			error("Syntax error.");
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
