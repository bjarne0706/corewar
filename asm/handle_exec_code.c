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

void			write_token()
{
// 	long str;
// 	char *str3;
// 	char *str2;

// 	str2 = ft_memalloc(4);
// 	str3 = ft_memalloc(1);

// 	str = 104 & 0xff;
// //	str3 = 0x0b;
// 	long str4;
// 	str4 = 0x0;
// 	str2 = ft_memcpy(str2, &str4, 4);
// 	write(g_files->s_fd, str2, 4);
// //	str = str & 0xff;
// //	printf("%s\n", ft_itoa_base(str, 16));
// //	str = ft_itoa_base(str, 16);
// 	str3 = ft_memcpy(str3, &str, 1);
// 	write(g_files->s_fd, str3, 1);
	t_oken		*tmp_tkn;
	t_tmp		*tmp_tmp;

	tmp_tmp = g_tmp_op;
	tmp_tkn = g_tkns;
	while (tmp_tmp != NULL && tmp_tkn != NULL)
	{

		tmp_tmp = tmp_tmp->next;
		tmp_tkn = tmp_tkn->next;	
	}
}