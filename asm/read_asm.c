/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:55:19 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 18:55:24 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		read_asm_put_code_size(void)
{
	char	*line;

	while (get_next_line(g_files->s_fd, &line) > 0)
	{
		disassemble_line(line);
		free(line);
	}
}

void		disassemble_line(char *line)
{

}