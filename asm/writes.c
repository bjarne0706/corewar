/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:15:45 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 14:15:47 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			write_header()
{
	char		*tmp;
	long int	i;

	tmp = (char *)ft_memalloc(4);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	tmp = ft_memcpy(tmp, &i, 4);
	write(g_files->s_fd, tmp, 4);
	free(tmp);
}

int				write_name(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	long int	num;
	int 		i;

	i = 0;
	num = PROG_NAME_LENGTH;
	g_str->name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	g_str->name = ft_memcpy(g_str->name, tmp_name, num);
	return (1);
}

int				write_comment(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	long int	num;
	int 		i;

	i = 0;
	num = COMMENT_LENGTH;
	g_str->comment = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	g_str->comment = ft_memcpy(g_str->comment, tmp_name, num);
	return (1);
}
