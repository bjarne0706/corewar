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

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../op.h"

# define f printf("KEK\n");
# define f2 printf("KEK2\n");
# define f3 printf("KEK3\n");
# define f4 printf("KEK4\n");

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

typedef struct		s_op
{
	char			*name;
	long			code;
	long 			arg_count;
	uint8_t			argums[3];
	long			cycles;
	int 			arg_code_type;
	u_int8_t		t_dir_size;

}					t_op;

typedef struct		s_oken
{
	t_op			*token;
	char 			*label;
	struct s_oken	*next;
}					t_oken;

typedef struct		s_file
{
	char			*line;
	struct s_file	*next;
}					t_file;

t_file				*g_file;
t_files				*g_files; // files
t_strings			*g_str;// parts of .cor file
t_oken				*g_tkns; //tokens
char 				*g_cor_line;
long 				g_exec_size;
//asm_main
void				write_all(void);
char				*get_name(char *name);
char				*ft_itoa_base(int value, int base);
//writes
void				write_header();
int					write_name(char *line);
int					write_comment(char *line);
void				write_token();
//addit_for_writes
int					search_bracks(char *line);
int 				search_r_bracks(char *line, int num);
char 				*read_betw_brack(char *str);
unsigned int		reverse_byte(unsigned int num);
void				error(char *str);
//read_asm
void				read_asm_put_code_size();
void				disassemble_line(char *line);
void				create_token(char *line, t_oken *tkn);
//void				create_token(void);
#endif