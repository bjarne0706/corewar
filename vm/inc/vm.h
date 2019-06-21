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
# include <limits.h>

# define LOG_LIVES	1
# define LOG_CYCLES	2
# define LOG_OPS	4
# define LOG_DEATHS	8
# define LOG_MOVES	16

typedef struct		s_colors
{
	int				champ_num;
	int				st_wait;
	int				live_wait;
}					t_colors;

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
	size_t			dashes;
}					t_champ;

typedef struct		s_carr
{
	int				id;
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
**			[4] (-e = 'e'= 32 / -E = 'E' = 64)
** dump_cycles: [0] -d; [1] -s
*/

typedef struct		s_vm
{
	char			options[5];
	int				dump_cycles[2];
	int8_t			log;
	uint8_t			arena[MEM_SIZE];
	t_colors		colors[MEM_SIZE];
	int				champs_num;
	t_champ			*champs[MAX_PLAYERS];
	t_champ			*last_standing;
	t_carr			*carrs;
	size_t			carrs_num;
	size_t			cycles;
	size_t			cyc_since_check;
	size_t			lives_since_check;
	size_t			prev_lives;
	size_t			checks_done;
	int32_t			cyc_to_die;
	WINDOW			*info;
	WINDOW			*game;
	long			speed;
}					t_vm;

typedef struct			s_op
{
	char			*name;
	uint8_t			code;
	uint8_t			ar_num;
	int				types_byte;
	uint8_t			types[3];
	uint32_t		cycles;
	int				carry;
	uint8_t			t_dir_size;
}					t_op;

static t_op g_ops[17] =
{
	{"live", 0x01, 1, false, {T_DIR, 0, 0}, 10, false, 4},                         //1
	{"ld", 0x02, 2, true, {T_DIR | T_IND, T_REG, 0}, 5, true, 4},//2
	{"st", 0x03, 2, true, {T_REG, T_IND | T_REG}, 5, false, 4},//3
	{"add", 0x04, 3, true, {T_REG, T_REG, T_REG}, 10, true, 4},//4
	{"sub", 0x05, 3, true, {T_REG, T_REG, T_REG}, 10, true, 4},//5
	{"and", 0x06, 3, true, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, true, 4},//6
	{"or", 0x07, 3, true, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, true, 4},//7
	{"xor", 0x08, 3, true, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, true, 4},//8
	{"zjmp", 0x09, 1, false, {T_DIR, 0, 0}, 20, false, 2},//9
	{"ldi", 0x0a, 3, true, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, false, 2},//10
	{"sti", 0x0b, 3, true, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, false, 2},//11
	{"fork", 0x0c, 1, false, {T_DIR, 0, 0}, 800, false, 2},//12
	{"lld", 0x0d, 2, true, {T_DIR | T_IND, T_REG, 0}, 10, true, 4},//13
	{"lldi", 0x0e, 3, true, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, true, 2},//14
	{"lfork", 0x0f, 1, false, {T_DIR, 0, 0}, 1000, false, 2},//15
	{"aff", 0x10, 1, true, {T_REG, 0, 0}, 2, false, 4},//16
	{0, 0, 0, 0, {0, 0, 0}, 0, 0, 0}
};

void		op_live(t_vm *v, t_carr *c, t_op *op);
void		op_ld(t_vm *v, t_carr *c, t_op *op);
void		op_st(t_vm *v, t_carr *c, t_op *op);
void		op_add(t_vm *v, t_carr *c, t_op *op);
void		op_sub(t_vm *v, t_carr *c, t_op *op);
void		op_and(t_vm *v, t_carr *c, t_op *op);
void		op_or(t_vm *v, t_carr *c, t_op *op);
void		op_xor(t_vm *v, t_carr *c, t_op *op);
void		op_zjmp(t_vm *v, t_carr *c, t_op *op);
void		op_ldi(t_vm *v, t_carr *c, t_op *op);
void		op_sti(t_vm *v, t_carr *c, t_op *op);
void		op_fork(t_vm *v, t_carr *c, t_op *op);
void		op_lld(t_vm *v, t_carr *c, t_op *op);
void		op_lldi(t_vm *v, t_carr *c, t_op *op);
void		op_lfork(t_vm *v, t_carr *c, t_op *op);
void		op_aff(t_vm *v, t_carr *c, t_op *op);

static void (*g_func_arr[16])(t_vm *v, t_carr *c, t_op *op) = 
{
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

/*
** Parse flags
*/

void				parse_vm_args(int ac, char *av[], t_vm *v);
void				flag_d(char *av[], int ac, int *i, t_vm *v);
void				flag_s(char *av[], int ac, int *i, t_vm *v);
void				flag_l(char *av[], int ac, int *i, t_vm *v);
void				flag_e(char *av[], int *i, t_vm *v);

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
void				add_carriage(t_carr **carr, t_champ *chmp,
						unsigned int pos);

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
void				update_options(t_vm *v);

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

void				log_cycles(size_t cycles);
void				log_deaths(t_vm *v, t_carr *del);
void				log_moves(t_vm *v, t_carr *c);

/*
** Byebye
*/

void				vm_error(char *msg);
void				byebye_our_darling(t_vm *v);

/*
** Visuals
*/

int		interface(WINDOW *menu, t_vm *v);
void	create_border(t_vm *v);
void	del_win(WINDOW *game, WINDOW *info);
void	car_loop(t_vm *v, WINDOW *game, WINDOW *info);
void	print_and_refresh2(t_vm *v);
void	*animation(WINDOW *picture);
void	*inter_loop(WINDOW *menu, t_vm *v);
void	start_menu(t_vm *v);
void	screen_and_color(void);
void	core_img(WINDOW *core, int ymax, int xmax);
void	winner(t_vm *v);
void	print_players(t_vm *v);
void	dash_line(t_vm *v);
void	dash_line2(t_vm *v);
void	print_and_refresh(t_vm *v);
void	authors(WINDOW *menu);





///DEBUG
void				print_champs(t_vm *v);
void				print_carriages(t_vm *v);
void				print_vm_params(t_vm *v);
void				print_color_map(t_vm *v);

#endif
