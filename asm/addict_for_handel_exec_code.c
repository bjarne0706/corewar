/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addict_for_handel_exec_code.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:13:03 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/06 16:13:06 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		fill_type_code(int count, char **code)
{
	int		i;

	i = count * 2;
	while (i < 8)
		(*code)[i++] = '0';
	(*code)[i] = '\0';
}

void		free_and_ret(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_strdel(&arr[i]);
	free(arr);
}

void		free_structs()
{
	// t_oken	*tmp;

	// tmp = g_tkns;
	// while (tmp != NULL)
	// {
	// 	free(tmp->code_types);
	// 	tmp = tmp->next;
	// }
	free(g_str->name);
	free(g_str->comment);
	ft_bzero(g_str, sizeof(t_strings));
	ft_bzero(g_files, sizeof(t_files));
}