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
	int				code_size;
	int				mem_pos;
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

static t_op    g_op_tab[17] =
		{
			{"live", 0x01, 1, {T_DIR}, 10, 0, 4},                         //1
			{"ld", 0x02, 2, {T_DIR | T_IND, T_REG}, 5, 1, 4},//2
			{"st", 0x03, 2, {T_REG, T_IND | T_REG}, 5, 1, 4},//3
			{"add", 0x04, 3, {T_REG, T_REG, T_REG}, 10, 1, 4},//4
			{"sub", 0x05, 3, {T_REG, T_REG, T_REG}, 10, 1, 4},//5
			{"and", 0x06, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},//6
			{"or", 0x07, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},//7
			{"xor", 0x08, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},//8
			{"zjmp", 0x09, 1, {T_DIR}, 20, 0, 2},//9
			{"ldi", 0x0a, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2},//10
			{"sti", 0x0b, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2},//11
			{"fork", 0x0c, 1, {T_DIR}, 800, 0, 2},//12
			{"lld", 0x0d, 2, {T_DIR | T_IND, T_REG}, 10, 1, 4},//13
			{"lldi", 0x0e, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2},//14
			{"lfork", 0x0f, 1, {T_DIR}, 1000, 0, 2},//15
			{"aff", 0x10, 1, {T_REG}, 2, 1, 4},//16
			{0, 0, 0, {0}, 0, 0, 0}
		};
		
t_tmp				*g_tmp_op;
t_file				*g_file;
t_files				*g_files;			// files
t_strings			*g_str;				// parts of .cor file
t_oken				*g_tkns;			// tokens
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
void				create_token();
int					get_op_name();
int					choose_name(char *line);
void				work_on_op(int num, t_tmp *tmp);
void				fill_token(int num, t_oken *tkn);
void				fill_args(int num, t_tmp *tmp1, t_oken *new);
int					trim_space(int i, char *line);
void				handle_args(char **arr, t_oken *new, int num, t_tmp *tmp);
//handle_exec_code
void				analize_token(t_tmp *line, t_oken *tkn);
uint8_t				get_value_of_arg(char *arg, int *pos, t_oken *tkn);
u_int8_t			work_on_label(char *arg, int pos);
//void				create_token(void);
#endif