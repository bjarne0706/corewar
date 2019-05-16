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


# define f printf("KEK\n");
typedef struct		s_files
{
	int 			f_fd;
	int 			s_fd;
}					t_files;

typedef struct		s_strings
{
	char 			*name;
	char 			*comment;
}					t_strings;

typedef struct		s_oken
{
	char			label;
	char 			inst;
	char
	char			arg2;
	char			arg2_type;
	char			arg3;
	char			arg3_type;
	struct s_oken	*next;
}					t_oken;

t_files				*g_files;
t_strings			*g_str;
char 				*g_cor_line;
//asm_main
void				error(char *str);
unsigned int		reverse_byte(unsigned int num);
void				write_header();
char				*get_name(char *name);
char 				*read_betw_brack(char *str);
void				write_exec_code_size();
void				write_name(char *line);
void				write_comment(char *line);
void				write_token();
#endif //COREWAR_COREWAR_H
