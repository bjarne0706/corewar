/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:55:39 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/13 19:55:40 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../op.h"

typedef struct	s_files
{
	int 		f_fd;
	int 		s_fd;
}				t_files;

t_files			*g_files;
char 			*g_cor_line;
//asm_main
void			error(char *str);
unsigned int	reverse_byte(unsigned int num);
void			write_header();
char			*get_name(char *name);
void			write_player_name();

#endif //COREWAR_COREWAR_H
