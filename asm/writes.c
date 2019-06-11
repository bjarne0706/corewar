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
	unsigned	i;
	
	g_full_line = ft_memalloc(PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	i = reverse_byte(COREWAR_EXEC_MAGIC);
	ft_memcpy(g_full_line, &i, 4);
	g_posit += 4;
}

int				write_name(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	char 		*tmp;
	long int	num;
	int 		i;

	i = 0;
	num = PROG_NAME_LENGTH;
	g_str->name = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	brack_flag = 0;
	tmp = tmp_name;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		free(tmp);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	ft_memcpy(g_str->name, tmp_name, num);
	free(tmp_name);
	return (1);
}

int				write_comment(char *line)
{
	int 		brack_flag;
	char 		*tmp_name;
	char 		*tmp;
	long int	num;
	int 		i;

	i = 0;
	num = COMMENT_LENGTH;
	g_str->comment = (char *)ft_memalloc(num);
	tmp_name = (char *)ft_memalloc(num);
	tmp = tmp_name;
	brack_flag = 0;
	while (brack_flag != 2)
	{
		if ((i = search_bracks(line)))
			brack_flag++;
		if (search_r_bracks(line, i))
			brack_flag++;
		tmp_name = ft_strjoin(tmp_name, line);
		free(tmp);
		if (brack_flag != 2)
			get_next_line(g_files->f_fd, &line);
	}
	tmp_name = read_betw_brack(tmp_name);
	ft_memcpy(g_str->comment, tmp_name, num);
	free(tmp_name);
	return (1);
}

void		put_hex(int32_t nbr, int size)
{
	unsigned int	tmp;
	int				i;
	unsigned int	max;
	char			*res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		tmp = max + nbr + 1;
	else
		tmp = nbr;
	res = (char *)malloc(size);
	i = size;
	while (--i >= 0)
	{
		res[i] = tmp % 256;
		tmp /= 256;
	}
	ft_memcpy(g_full_line + g_posit, res, size);
	g_posit += size;
	free(res);
}

void		print_args(t_oken *tkn)
{
	int		size;
	int		y;
	t_tmp	*tmp;

	tmp = g_tmp_op;
	y = 0;
	while (y < tkn->token->arg_count)
	{
		if (tkn->args_type[y] == 1)
			size = 1;
		else if (tkn->args_type[y] == 2)
			size = tkn->token->t_dir_size;
		else if (tkn->args_type[y] == 3)
			size = 2;
		put_hex((int32_t)tkn->token->argums[y], size);
		y++;
	}
}