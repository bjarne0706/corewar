/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addict_for_read_asm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:19:31 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/21 15:19:34 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		handle_args(char **arr, t_oken *new, int num)
{
	int		y;

	y = 0;
	while (arr[y])
	{
		handle_args_while(arr[y], y, new, num);
		if (!validate_arg(arr[y], new->args_type[y]))
			error("Error: syntax error in argument.");
		if (!(new->args_type[y] & g_op_tab[num].argums[y]))
			error("Error: incorrect argument type.");
		new->args_value[y] = ft_strdup(arr[y]);
		y++;
	}
	if (y != g_op_tab[num].arg_count)
		error("Error: too few argument.");
	num = 1;
}

void		handle_args_while(char *arr, int y, t_oken *new, int num)
{
	int		x;

	del_space_end(&arr);
	x = trim_space(0, arr);
	if (arr[x] == 'r')
	{
		new->code_size++;
		g_exec_size++;
		new->args_type[y] = 1;
	}
	else if (arr[x] == '%')
	{
		new->code_size += g_op_tab[num].t_dir_size;
		g_exec_size += g_op_tab[num].t_dir_size;
		new->args_type[y] = 2;
	}
	else
	{
		new->code_size += 2;
		g_exec_size += 2;
		new->args_type[y] = 4;
	}
}

int			validate_arg(char *arg, int type)
{
	int		x;
	int		status;

	x = trim_space(0, arg);
	if (type == 1)
	{
		while (arg[++x])
			if (!ft_isdigit(arg[x]) && arg[x] != '-')
				status = 0;
	}
	else if (type == 2 && arg[x + 1] == LABEL_CHAR)
	{
		x++;
		while (arg[++x])
			if (ft_strchr(LABEL_CHARS, arg[x]) == 0)
				status = 0;
	}
	else
		status = validate_arg_p2(arg, type, x);
	return (status);
}

int			validate_arg_p2(char *arg, int type, int x)
{
	if (type == 2 && arg[x + 1] != LABEL_CHAR)
	{
		while (arg[++x])
			if (!ft_isdigit(arg[x]) && arg[x] != '-')
				return (0);
	}
	else
	{
		while (arg[++x])
			if (ft_strchr(LABEL_CHARS, arg[x]) == 0)
				return (0);
	}
	return (1);
}

void		check_labels_chars(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == 0)
			error("Syntax error in label.");
		i++;
	}
}
