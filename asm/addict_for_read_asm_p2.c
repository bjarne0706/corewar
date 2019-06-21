/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addict_for_read_asm_p2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:22:09 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/21 15:22:12 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		if ((line[i] == '#' || line[i] == ';') && abc_flag == 0)
		{
			g_new_l = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void		del_space_end(char **line)
{
	int		i;

	i = ft_strlen((*line)) - 1;
	while (i > 0 && ft_space((*line)[i]) && (*line)[i] != LABEL_CHAR &&
					(*line)[i] != DIRECT_CHAR)
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
	while (i > 0 && !ft_isalnum((*line)[i]) && (*line)[i] != LABEL_CHAR &&
					(*line)[i] != DIRECT_CHAR)
		i--;
	i++;
	(*line)[i] = '\0';
}

void		create_token(char *line)
{
	int		type_of_op;

	type_of_op = get_op_name(line, 0);
	work_on_op(type_of_op, line);
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
		else if (tkn->args_type[y] == 4)
			size = 2;
		put_hex(tkn->token->argums[y], size);
		y++;
	}
}
