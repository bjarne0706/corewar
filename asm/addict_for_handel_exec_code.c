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
	free(g_str->name);
	if (g_str->comment)
		free(g_str->comment);
	ft_bzero(g_str, sizeof(t_strings));
	ft_bzero(g_files, sizeof(t_files));
}

char		*ft_strjoin_three(char *s1, char *s2, char *s3, int num)
{
	char	*s_new;
	int		i;
	int		i2;
	int		i3;

	i3 = -1;
	i2 = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	s_new = ft_memalloc(i + 1);
	s_new[0] = '\0';
	i = -1;
	while (s1[++i])
		s_new[i] = s1[i];
	if (num)
	{
		if (i == COMMENT_LENGTH + 1)
			error("Error: too long comment");
	}
	else
		if (i == PROG_NAME_LENGTH + 1)
			error("Error: too long comment");
	i--;
	while (s2[++i2])
		s_new[++i] = s2[i2];
	while (s3[++i3])
		s_new[++i] = s3[i3];
	s_new[i + 1] = '\0';
	// free(s1);
	return (s_new);
}