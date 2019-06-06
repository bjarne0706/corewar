/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 20:30:22 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/22 20:30:24 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		put_exec_code(void)
{
	t_oken	*tmp_tkn;

	tmp_tkn = g_tkns;
	while (tmp_tkn != NULL)
	{
		put_hex((int32_t)tmp_tkn->token->code, 1);
		if (tmp_tkn->token->arg_code_type)
			put_hex((int32_t)make_from_binary(tmp_tkn->code_types), 1);
		print_args(tmp_tkn);
		tmp_tkn = tmp_tkn->next;
	}
}

int			make_from_binary(char *str)
{
	int		i;
	int		sum;
	int		mult;

	sum = 0;
	mult = 1;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '1')
			sum += mult;
		mult *= 2;
		i--;
	}
	return (sum);
}
//0b68 0100 0700 0101 0000 0000 0290 0000
//0000 0209 ffed

void		analize_token(t_tmp *line, t_oken *tkn)
{
	int		i;
	char	*type_code;

	type_code = ft_memalloc(8);
	i = 0;
	while (line->args[i] && i < tkn->token->arg_count)
	{
		tkn->token->argums[i] = get_value_of_arg(line->args[i], tkn, &type_code);
		i++;
	}
	fill_type_code(&type_code);
	if (tkn->token->arg_code_type)
		tkn->code_types = ft_strdup(type_code);
	else
		tkn->code_types = NULL;
}

int			get_value_of_arg(char *arg, t_oken *tkn, char **type_code)
{
	int		value;
	int		i;

	i = trim_space(0, arg);
	value = 0;
	if (arg[i] == 'r')
	{
		value = ft_atoi(&arg[i + 1]);
		if (value < 0 || value > 99)
			error("Incorrect register");
		(*type_code) = ft_strjoin((*type_code), "01");
	}
	else if (arg[i] == '%' && arg[i + 1] == ':')
	{
		value = work_on_label(tkn, &arg[i + 2]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else if (arg[i] == '%')
	{
		value = ft_atoi(&arg[i + 1]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else
	{
		value = ft_atoi(&arg[i]);
		(*type_code) = ft_strjoin((*type_code), "11");
	}
	return (value);
}

int				work_on_label(t_oken *tkn, char *arg)
{
	t_oken		*tmp;
	int			value;

	value = 0;
	tmp = g_tkns;
	while (tmp->next != NULL)
	{
		if (tmp->label)
			if (ft_strcmp(tmp->label, arg) == 0)
			{
				value = tmp->mem_pos - tkn->mem_pos;
				break ;
			}
		tmp = tmp->next;
	}
	return (value);
}