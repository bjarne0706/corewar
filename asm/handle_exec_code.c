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

void		write_token()
{
	// long str;
	// char *str3;
// 	char *str2;

	// str2 = ft_memalloc(4);
	// str3 = ft_memalloc(1);

	// str = 104 & 0xff;
// //	str3 = 0x0b;
// 	long str4;
// 	str4 = 0x0;
// 	str2 = ft_memcpy(str2, &str4, 4);
// 	write(g_files->s_fd, str2, 4);
// //	str = str & 0xff;
// //	printf("%s\n", ft_itoa_base(str, 16));
// //	str = ft_itoa_base(str, 16);
	// str3 = ft_memcpy(str3, &str, 1);
	// write(g_files->s_fd, str3, 1);
	t_oken		*tmp_tkn;
	t_tmp		*tmp_tmp;

	tmp_tmp = g_tmp_op;
	tmp_tkn = g_tkns;
	while (tmp_tmp != NULL && tmp_tkn != NULL)
	{
		analize_token(tmp_tmp, tmp_tkn);
		tmp_tmp = tmp_tmp->next;
		tmp_tkn = tmp_tkn->next;	
	}
}

void		analize_token(t_tmp *line, t_oken *tkn)
{
	int		mem_pos;
	int		i;

	i = 0;
	mem_pos = 1 + tkn->mem_pos;
	if (tkn->token->arg_code_type == 1)
		mem_pos++;
	while (line->args[i] && i < 3)
	{
		printf("i:%d\n", i);
		printf("arguments: %p\n", line->args[i]);
		tkn->token->argums[i] = get_value_of_arg(line->args[i], &mem_pos, tkn);
		i++;
	}
}

uint8_t		get_value_of_arg(char *arg, int *pos, t_oken *tkn)
{
	uint8_t value;
	int		i;
f
	i = trim_space(0, arg);
	value = 0;
	printf("argums:%s\n", arg);
	if (arg[i] == 'r')
	{
		value = (u_int8_t)ft_atoi(&arg[i + 1]);
		(*pos)++;
	}
	else if (arg[i] == '%' && arg[i + 1] == ':')
	{
		value = work_on_label(&arg[i + 2], *pos);
		(*pos) += tkn->token->t_dir_size;
	}
	else if (arg[i] == '%')
	{
		value = (u_int8_t)ft_atoi(&arg[i + 1]);
		(*pos) += tkn->token->t_dir_size;
	}
	else
	{
		value = (u_int8_t)ft_atoi(&arg[i]);
		(*pos) += 2;		
	}
	printf("position: %d\n", *pos);
	printf("value:%d\n", value);
	return (value);
}

u_int8_t	work_on_label(char *arg, int pos)
{
	t_oken		*tmp;
	u_int8_t	value;

	value = 0;
	tmp = g_tkns;
	while (tmp->next != NULL )
	{
		if (tmp->label)
			if (ft_strcmp(tmp->label, arg) == 0)
				value = tmp->mem_pos - pos;
		tmp = tmp->next;
	}
	return (value);
}