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

void		free_structs(void)
{
	if (g_str->name)
		ft_strdel(&g_str->name);
	if (g_str->comment)
		ft_strdel(&g_str->comment);
	if (g_str)
		ft_bzero(g_str, sizeof(t_strings));
	if (g_files)
		ft_bzero(g_files, sizeof(t_files));
}
