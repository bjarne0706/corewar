/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addict_for_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:09:18 by dchantse          #+#    #+#             */
/*   Updated: 2019/06/21 15:09:25 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int			check_line(char *str)
{
	int		i;

	i = trim_space(0, str);
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_space(str[i]) && str[i] != SEPARATOR_CHAR &&
			str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR &&
			!ft_isalnum(str[i]) && str[i] != '-' &&
			!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			if_has_smthng(char *line)
{
	int		i;
	int		sum;

	sum = 0;
	i = -1;
	while (line[++i])
		if (ft_isalnum(line[i]) || ft_strchr(LABEL_CHARS, line[i])
		|| line[i] == LABEL_CHAR || line[i] == DIRECT_CHAR
		|| line[i] == SEPARATOR_CHAR)
			sum++;
	if (sum == 0)
		return (0);
	return (1);
}

int			trim_space(int i, char *line)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int			validate_comment_cmd(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i] != COMMENT_CMD_STRING[0])
		if (!ft_space(str[i]))
			error("Syntax error in comment command.");
	i--;
	while (str[++i] != '"' && !ft_space(str[i]) && str[i])
		if (str[i] != COMMENT_CMD_STRING[j++])
			error("Syntax error in comment command.");
	while (str[i] != '"' && ft_space(str[i]) && str[i])
		i++;
	if (str[i] == '\0' || str[i] != '"')
		error("Syntax error in comment command.");
	return (i);
}
