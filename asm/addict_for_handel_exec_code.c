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

void		ft_strjoin_three(char **s1, char *s2, char *s3, int num)
{
	int		i;
	int		i2;
	int		i3;

	i3 = -1;
	i2 = -1;
	if (s1 == NULL || s2 == NULL)
		return ;
	i = ft_strlen((*s1));
	// printf("ft_strlen(s1): %d ft_strlen(s2): %d\n", ft_strlen((*s1)), ft_strlen(s2));
	while (s2[++i2])
	{
	// printf("i: %d i2: %d\n", i, i2);
		if (num)
		{
			if (i == COMMENT_LENGTH || i2 == COMMENT_LENGTH)
			{
				ft_strdel(&g_str->comment);
				ft_strdel(s1);
				error("Error: too long comment.");
			}
		}
		else if (i == PROG_NAME_LENGTH || i2 == PROG_NAME_LENGTH)
		{
			ft_strdel(&g_str->name);
			ft_strdel(s1);
			error("Error: too long name.");
		}
		(*s1)[++i] = s2[i2];
	}
	while (s3[++i3])
		(*s1)[++i] = s3[i3];
	(*s1)[i + 1] = '\0';
}
