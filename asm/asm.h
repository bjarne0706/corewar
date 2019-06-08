/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:55:39 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/22 10:56:24 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/includes/libft.h"
# include "../our_op.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

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

typedef struct		s_oken
{
	t_op			*token;
	int				args_type[3];
	char 			*label;
	int				code_size;
	int				mem_pos;
	char			*code_types;
	struct s_oken	*next;
}					t_oken;

typedef struct		s_file
{
	char			*line;
	struct s_file	*next;
}					t_file;

typedef struct		s_tmp
{
	char			*op;
	char			**args;
	char			*label;
	int				code_size;
	struct s_tmp	*next;
}					t_tmp;
unsigned char		*g_full_line;
int					g_posit;
t_tmp				*g_tmp_op;
t_file				*g_file;
t_files				*g_files;
t_strings			*g_str;
t_oken				*g_tkns;
char 				*g_cor_line;
long 				g_exec_size;
//asm_main
void				write_all(void);
char				*get_name(char *name);
void				write_token();
//writes
void				write_header();
int					write_name(char *line);
int					write_comment(char *line);
void				put_hex(int32_t nbr, int size);
void				print_args(t_oken *tkn);
//addit_for_writes
int					search_bracks(char *line);
int 				search_r_bracks(char *line, int num);
char 				*read_betw_brack(char *str);
unsigned int		reverse_byte(unsigned int num);
void				error(char *str);
//read_asm
void				read_asm_put_code_size();
void				disassemble_line(char *line);
void				create_token();
void				work_on_op(int num, t_tmp *tmp);
void				handle_args(char **arr, t_oken *new, int num, t_tmp *tmp);
//addict_func_for_read_asm
int					label_char_pos(char *str);
int					ft_space(char c);
int					count_separ(char *str);
int					trim_space(int i, char *line);
int					choose_name(char *line);
//find_op_and_fill_args
void				fill_token(int num, t_oken *tkn);
void				fill_args(int num, t_tmp *tmp1, t_oken *new);
int					if_has_smthng(char *line);
int					find_op(char *line);
int					get_op_name();
int					check_line(char *str);
//handle_exec_code
void				analize_token(t_tmp *line, t_oken *tkn);
int					get_value_of_arg(char *arg, t_oken *tkn, char **type_code);
int					work_on_label(t_oken *tkn, char *arg);
void				put_exec_code(void);
int					make_from_binary(char *str);
//addict_for_handle_exec_code
void				fill_type_code(char **code);
#endif