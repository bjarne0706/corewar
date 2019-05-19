/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:55:19 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 18:55:24 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		read_asm_put_code_size(void)
{
	char	*line;

	while (get_next_line(g_files->s_fd, &line) > 0)
	{
		if (line[0] !='\n')
			disassemble_line(line);
		free(line);
	}
}

void		disassemble_line(char *line)
{
	t_oken	*tmp;
	t_oken	*new;

	new = (t_oken *)ft_memalloc(sizeof(t_oken));
	if (g_tkns == NULL) {
		g_tkns = new;
	}
	else
	{
		tmp = g_tkns;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (ft_strchr(line, LABEL_CHAR) != 0)
	{
		new->label = ft_strdup(line);
		free(line);
		get_next_line(g_files->f_fd, &line);
		create_token(line, new);
	}
	else
		create_token(line, new);
}

void		create_token(char *line, t_oken *tkn)
{
	char	*op_name;


}

//void		create_token(void)
//{
//
//}
