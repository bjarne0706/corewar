/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:34:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/16 15:34:49 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/includes/libft.h"
# include "../../op.h"

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <ncurses.h>
# include <limits.h>	//?

# define LOG_LIVES	1
# define LOG_CYCLES	2
# define LOG_OPS	4
# define LOG_DEATHS	8
# define LOG_MOVES	16

typedef struct		s_champ
{
	int				num;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	uint32_t		size;
	uint8_t			code[CHAMP_MAX_SIZE];
	size_t			last_live_cyc;
	size_t			current_lives;
	size_t			prev_lives;
}					t_champ;

typedef struct		s_carr
{
	int			 	id;
	t_champ			*champ;
	int32_t			pc;
	uint8_t			op;
	int				wait_cycles;
	uint8_t			arg_types[3];
	uint32_t		step;
	size_t			last_live;
	int				carry;
	int32_t			reg[REG_NUMBER];
	struct s_carr	*nxt;
}					t_carr;

/*
** options: [0] (-dump/-d = 'd' = 32 | -D = 'D' = 64); 
**			[1] (-s = 's' = 32 | -S = 'S' = 64);
**			[2] -v
**			[3] -a
** dump_cycles: [0] -d; [1] -s
*/

typedef struct		s_vm
{
	char			options[4];
	int				dump_cycles[2];
	int8_t			log;
	uint8_t			arena[MEM_SIZE];
	uint8_t			colors[MEM_SIZE];
	int				champs_num;
	t_champ			*champs[MAX_PLAYERS];
	t_champ			*last_standing;
	t_carr			*carrs;
	size_t			carrs_num;
	size_t			cycles;
	size_t			cyc_since_check;
	size_t			lives_since_check;
	size_t			checks_done;
	int32_t			cyc_to_die;
	WINDOW			*info;
	WINDOW 			*game;
}					t_vm;

# include "vm_op.h"
# include "visual.h"

/*
** Parse flags
*/

void				parse_args(int ac, char *av[], t_vm *v);
void				flag_d(char *av[], int ac, int *i, t_vm *v);
void				flag_s(char *av[], int ac, int *i, t_vm *v);
void				flag_l(char *av[], int ac, int *i, t_vm *v);

/*
** Parse players
*/

void				flag_n(char *av[], int ac, int *i, t_vm *v);
int					find_champ(t_vm *v, int n);
int					cor_filename(const char *s);
void				parse_champ(t_vm *v, char *filecor, int n);
int					validate_magic(int fd);
int					parse_name(int fd, t_champ *champ);
void				parse_size_and_comment(int fd, t_champ *ch);
void				validate_champ_nums(t_vm *v);
void				assign_champ_nums(t_vm *v);
void				rearrange_champs(t_vm *v);

/*
** Init
*/

t_vm				*init_vm(void);
t_champ				*add_champ(int n);
void				setup_arena(t_vm *v);
void				setup_carriages(t_vm *v);
void				add_carriage(t_carr **carr, t_champ *chmp, unsigned int pos);

/*
** Game
*/

void				run_the_game(t_vm *v);
void				die_check(t_vm *v);

/*
** Cycle
*/

void				run_cycle(t_vm *v);
void				process_carriage(t_vm *v, t_carr *c);

/*
** Parse args
*/

int					validate_args_types(t_vm *v, t_carr *c, t_op *op);
void				byte_to_arr3(uint8_t *arg_types, unsigned char byte);
int					validate_reg_args(t_vm *v, t_carr *c, t_op *op);

/*
** Printer
*/

void				print_usage(void);
void				introduce_champs(t_vm *v);
void				print_arena(t_vm *v, char flag);
void				hail_the_hero(t_vm *v);

/*
** Utils
*/

unsigned int		reverse_byte(unsigned int num);
uint32_t			step_calc(t_carr *c, t_op *op);
uint32_t			arg_size(uint8_t arg_type, t_op *op);
int32_t				calc_address(int32_t pc, int idx_mode, int32_t step);

int32_t				get_int(t_vm *v, int pc, int size);
void				int_to_arena(t_vm *v, int32_t pos, t_carr *c, int32_t num);
int32_t				get_arg(t_vm *v, t_carr *c, uint8_t idx, int32_t *pc);
int32_t				get_arg_and(t_vm *v, t_carr *c, size_t num, size_t pc);

/*
** Carriages
*/

void				copy_carriage(t_vm *v, t_carr *c, int32_t pos);
void				kill_those_loosers(t_vm *v);
void				slaughter_carriage(t_vm *v, t_carr *slow, t_carr *fast);

/*
** Logs
*/

void            	log_cycles(size_t cycles);
void            	log_deaths(t_vm *v, t_carr *del);
void        	    log_moves(t_vm *v, t_carr *c);

/*
** Byebye
*/

void				vm_error(char *msg);

///DEBUG
void			print_champs(t_vm *v);
void			print_carriages(t_vm *v);
void			print_vm_params(t_vm *v);
void			print_color_map(t_vm *v);

#endif
