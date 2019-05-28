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
	put_exec_code();
}

void		put_exec_code(void)
{
	t_tmp	*tmp_tmp;
	t_oken	*tmp_tkn;

	tmp_tkn = g_tkns;
	tmp_tmp = g_tmp_op;
	while (tmp_tmp != NULL && tmp_tkn != NULL)
	{
		print_op_code(tmp_tkn->token->code);
		if (tmp_tkn->token->arg_code_type)
			print_code_type(tmp_tkn->code_types);
		print_args(tmp_tkn);
		tmp_tmp = tmp_tmp->next;
		tmp_tkn = tmp_tkn->next;
	}
}

void		print_op_code(long code)
{
	char	*str;

	str = ft_memalloc(1);
	code = code & 0xff;
	str = ft_memcpy(str, &code, 1);
	write(g_files->s_fd, str, 1);
}

void		print_code_type(char *str)
{
	int		num;
	char	*mas;

	num = make_from_binary(str);
	mas = ft_memalloc(1);
	num = num & 0xff;
	mas = ft_memcpy(mas, &num, 1);
	write(g_files->s_fd, mas, 1);
}

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
		// printf("str[i]: %c mult: %d sum: %d\n",str[i], mult, sum);
		i--;
	}
	printf("sumsumsum: %d\n", sum);
	return (sum);
}
//0b68 0100 0700 0101 0000 0000 0290 0000
//0000 0209 ffed
void		print_args(t_oken *tkn)
{
	int		size;
	int		y;
	char	*str;
	t_tmp	*tmp;

	tmp = g_tmp_op;
	y = 0;
	printf("token name: %s\n", tkn->token->name);
	while (y < tkn->token->arg_count)
	{
		// printf("argums: %d\n", y);
		// printf("TYPE: %d ", tkn->args_type[y]);
		// printf("argums: %d\n", tkn->token->argums[y]);
		if (tkn->args_type[y] == 1)
			size = 1;
		else if (tkn->args_type[y] == 2)
			size = tkn->token->t_dir_size;
		else if (tkn->args_type[y] == 3)
			size = 2;
		// printf("SIZE: %d\n", size);
		str = ft_memalloc(size);
		if (tkn->token->argums[y] < 0)
		{
			tkn->token->argums[y] = make_neg_num(tkn->token->argums[y]) & 0xff;
			// printf("THIIIIIS: %x\n", tkn->token->argums[y]);
		}
		else
				tkn->token->argums[y] = tkn->token->argums[y] & 0xff;
		str = ft_memcpy(str, &tkn->token->argums[y], size);
		write(g_files->s_fd, str, size);
		ft_strdel(&str);
		y++;
	}
}

int			make_neg_num(int num)
{
	char	*number;
	int		i;
	char	*num2;
	int		size;

	num2 = ft_memalloc(16);
	i = 0;
	number = ft_itoa_base(num, 2);
	size = 16 - ft_strlen(number);
	while (i < size)
	{
		num2[i] = '0';
		i++;
	}
	num2 = ft_strjoin(num2, number);
	swap_0_to_1(&num2);
	return (make_from_binary(num2));
}

void		swap_0_to_1(char **num)
{
	int		i;

	i = 0;
	while ((*num)[i])
	{
		if ((*num)[i] == '1')
			(*num)[i] = '0';
		else
			(*num)[i] = '1';
		i++;
	}
	(*num)[i - 1] = '1';
}

void		analize_token(t_tmp *line, t_oken *tkn)
{
	int		i;
	char	*type_code;

	type_code = ft_memalloc(8);
	i = 0;
	while (line->args[i] && i < 3)
	{
		tkn->token->argums[i] = get_value_of_arg(line->args[i], tkn, &type_code);
		printf("value in %s token: %d\n", tkn->token->name, tkn->token->argums[i]);
		i++;
	}
	fill_type_code(&type_code);
	if (tkn->token->arg_code_type)
		tkn->code_types = ft_strdup(type_code);
	else
		tkn->code_types = NULL;
}

void		fill_type_code(char **code)
{
	int		i;

	i = ft_strlen((*code)) - 1;
	while (++i != 8)
		(*code)[i] = '0';
}

int			get_value_of_arg(char *arg, t_oken *tkn, char **type_code)
{
	int		value;
	int		i;

	i = trim_space(0, arg);
	value = 0;
	if (arg[i] == 'r')
	{
		value = ft_atoi(&arg[i + 1]);
		(*type_code) = ft_strjoin((*type_code), "01");
	}
	else if (arg[i] == '%' && arg[i + 1] == ':')
	{
		value = work_on_label(tkn, &arg[i + 2]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else if (arg[i] == '%')
	{
		value = ft_atoi(&arg[i + 1]);
		(*type_code) = ft_strjoin((*type_code), "10");
	}
	else
	{
		value = ft_atoi(&arg[i]);
		(*type_code) = ft_strjoin((*type_code), "11");
	}
	return (value);
}

int				work_on_label(t_oken *tkn, char *arg)
{
	t_oken		*tmp;
	int			value;

	value = 0;
	tmp = g_tkns;
	while (tmp->next != NULL )
	{
		if (tmp->label)
			if (ft_strcmp(tmp->label, arg) == 0)
			{
				value = tmp->mem_pos - tkn->mem_pos;
				break ;
			}
		tmp = tmp->next;
	}
	return (value);
}