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
# include <limits.h>	//?

typedef struct		s_champ
{
	int				num;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned int	size;
	unsigned char	code[CHAMP_MAX_SIZE];

}					t_champ;

typedef struct		s_carr
{
	int			 	id;
	t_champ			*champ;
	int				pos;
	unsigned char	op;
	int				wait_cycles;
	unsigned int	step;
	size_t			last_live;
	t_bool			carry;
	int				reg[REG_NUMBER];

	struct s_carr	*nxt;
}					t_carr;

/*
** options: [0] (-dump/-d = 'd' = 32 | -D = 'D' = 64); 
**			[1] (-s = 's' = 32 | -S = 'S' = 64);
**			[2] -v
** dump_cycles: [0] -d; [1] -s
*/

typedef struct		s_vm
{
	char			options[4];
	int				dump_cycles[2];
	
	unsigned char	arena[MEM_SIZE];
	int				champs_num;
	t_champ			*champs[MAX_PLAYERS];
	t_champ			*last_standing;
	t_carr			*carrs;
	size_t			carrs_num;
	size_t			cycles;
	size_t			cycles_to_die;
	size_t			lives_in_cycle;
	size_t			checks_done;

}					t_vm;

void				parse_args(int ac, char *av[], t_vm *v);
void				flag_d(char *av[], int ac, int *i, t_vm *v);
void				flag_s(char *av[], int ac, int *i, t_vm *v);
void				flag_v(t_vm *v);

void				flag_n(char *av[], int ac, int *i, t_vm *v);
t_bool				find_champ(t_vm *v, int n);
t_bool				cor_filename(const char *s);
void				parse_champ(t_vm *v, char *filecor, int n);
t_bool				validate_magic(int fd);
t_bool				parse_name(int fd, t_champ *champ);
void				parse_size_and_comment(int fd, t_champ *ch);
void				validate_champ_nums(t_vm *v);
void				assign_champ_nums(t_vm *v);
void				rearrange_champs(t_vm *v);

t_vm				*init_vm(void);
t_champ				*add_champ(int n);
void				setup_arena(t_vm *v);
void				setup_carriages(t_vm *v);

void				print_usage(void);
void				introduce_champs(t_vm *v);
void				print_arena(t_vm *v, char flag);

unsigned int		reverse_byte(unsigned int num);

void				vm_error(char *msg);


///DEBUG
void			print_champs(t_vm *v);
void			print_carriages(t_vm *v);

#endif
