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

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/libft.h"
# include "../our_op.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_files
{
	int				f_fd;
	int				s_fd;
}					t_files;

typedef struct		s_strings
{
	char			*name;
	char			*comment;
}					t_strings;

typedef struct		s_oken
{
	t_op			*token;
	int				args_type[3];
	char			*args_value[3];
	char			*label;
	int				code_size;
	int				mem_pos;
	char			*code_types;
	struct s_oken	*next;
}					t_oken;

typedef struct		s_label
{
	char			*label;
	int				mem_pos;
	struct s_label	*next;
}					t_label;

unsigned char		*g_full_line;
int					g_posit;
t_files				*g_files;
t_strings			*g_str;
t_oken				*g_tkns;
t_label				*g_lbl;
long				g_exec_size;
/*
** asm_main
*/
void				write_all(int num, int status);
char				*get_name(char *name);
void				write_token();
/*
** writes
*/
void				write_header();
int					write_name(char *line, int j, int i, int flag);
int					write_comment(char *line, int j, int i, int flag);
void				write_name_p2(int *i, int *j, char **line, char **tmp_name);
void				write_comment_p2(int *i, int *j,
										char **line, char **tmp_name);
/*
** addit_for_writes
*/
unsigned int		reverse_byte(unsigned int num);
void				error(char *str);
void				check_size(char **str, int size, int type);
int					validate_name_cmd(char *str);
void				put_hex(int32_t nbr, int size);
/*
** read_asm
*/
void				read_asm_put_code_size(char *line);
void				read_asm_p2(char *line, char *tmp, char *tmp2);
void				create_token();
void				work_on_op(int num, char *line);
/*
** addict_for_read_asm
*/
void				handle_args(char **arr, t_oken *new, int num);
void				handle_args_while(char *arr, int y, t_oken *new, int num);
int					validate_arg(char *arg, int type);
int					validate_arg_p2(char *arg, int type, int x);
void				check_labels_chars(char *str);
/*
** addict_for_read_asm_p2
*/
void				make_lbl(char *str);
void				del_comment(char **line);
int					comment_line(char *line);
void				del_space_end(char **line);
void				print_args(t_oken *tkn);
/*
** addict_func_for_read_asm
*/
int					label_char_pos(char *str);
int					ft_space(char c);
int					count_separ(char *str);
int					choose_name(char *line);
int					choose_name_p2(char *line);
/*
** find_op_and_fill_args
*/
void				fill_token(int num, t_oken *tkn);
void				fill_args(int num, char *line, t_oken *new);
int					find_op(char *line, int sum, int i, int y);
int					get_op_name(char *line, int i);
void				find_op_p2(int i, int *sum, int y, char *line);
/*
** handle_exec_code
*/
void				analize_token(t_oken *tkn);
int					get_value(char *arg, t_oken *tkn, char **type_code);
int					work_on_label(t_oken *tkn, char *arg);
void				put_exec_code(void);
void				get_value_p2(char **arg, int *value,
									char **type_code, t_oken *tkn);
/*
** addict_for_handle_exec_code
*/
void				fill_type_code(int count, char **code);
void				free_and_ret(char **arr);
void				free_structs();
/*
**addict_for_all.c
*/
int					make_from_binary(char *str);
int					trim_space(int i, char *line);
int					validate_comment_cmd(char *str);
int					if_has_smthng(char *line);
int					check_line(char *str);
#endif
