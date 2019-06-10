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

void		fill_type_code(char **code)
{
	int		i;

	i = ft_strlen((*code)) - 1;
	while (++i != 8)
		(*code)[i] = '0';
}

void		free_and_ret(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_strdel(&arr[i]);
	free(arr);
}