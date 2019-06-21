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
	t_oken	*tkn;

	tkn = g_tkns;
	while (tkn != NULL)
	{
		put_hex((int32_t)tkn->token->code, 1);
		if (tkn->token->arg_code_type)
			put_hex(make_from_binary(tkn->code_types), 1);
		print_args(tkn);
		tkn = tkn->next;
	}
}

void		analize_token(t_oken *tkn)
{
	int		i;
	char	*type_code;

	type_code = (char *)ft_memalloc(sizeof(char) * 9);
	i = -1;
	while (tkn->args_value[++i] && i < tkn->token->arg_count)
		tkn->token->argums[i] = get_value(tkn->args_value[i], tkn, &type_code);
	fill_type_code(tkn->token->arg_count, &type_code);
	if (tkn->token->arg_code_type)
		tkn->code_types = ft_strdup(type_code);
	else
		tkn->code_types = NULL;
	free(type_code);
}

int			get_value(char *arg, t_oken *tkn, char **type_code)
{
	int		value;
	int		i;
	char	*tmp;

	tmp = (*type_code);
	i = trim_space(0, arg);
	value = 0;
	if (arg[i] == 'r')
	{
		if (!ft_isdigit(arg[i + 1]))
			error("Syntax error in register.");
		value = ft_atoi(&arg[i + 1]);
		if (value < 0 || value > 99)
			error("Incorrect register.");
		(*type_code) = ft_strjoin((*type_code), "01");
	}
	else if (arg[i] == '%' && arg[i + 1] == ':')
	{
		value = work_on_label(tkn, &arg[i + 2]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else
		get_value_p2(&arg, &value, type_code, tkn);
	free(tmp);
	return (value);
}

void		get_value_p2(char **arg, int *value, char **type_code, t_oken *tkn)
{
	int		i;

	i = trim_space(0, (*arg));
	if ((*arg)[i] == ':')
	{
		(*value) = work_on_label(tkn, &(*arg)[i + 1]);
		(*type_code) = ft_strjoin((*type_code), "11");
	}
	else if ((*arg)[i] == '%')
	{
		if ((!ft_strchr(LABEL_CHARS, (*arg)[i + 1]) &&
			(*arg)[i + 1] != '-') || (*arg)[i + 1] == '\0')
			error("Syntax error.");
		if ((*arg)[i + 1] == '-' && !ft_isdigit((*arg)[i + 2]))
			error("Error: incorrect argument.");
		(*value) = ft_atoi(&(*arg)[i + 1]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else
	{
		if ((*arg)[i] == '-' && !ft_isdigit((*arg)[i + 1]))
			error("Error: incorrect argument.");
		(*value) = ft_atoi(&(*arg)[i]);
		(*type_code) = ft_strjoin((*type_code), "11");
	}
}

int			work_on_label(t_oken *tkn, char *arg)
{
	t_label		*tmp;
	int			value;

	value = 0;
	tmp = g_lbl;
	while (tmp != NULL)
	{
		if (tmp->label)
			if (ft_strcmp(tmp->label, arg) == 0)
			{
				value = tmp->mem_pos - tkn->mem_pos;
				break ;
			}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		error("Error: label does not exist.");
	return (value);
}
