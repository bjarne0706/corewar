/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:58:28 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/29 18:58:31 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP_H
# define VM_OP_H

# include "vm.h"

typedef struct			s_op
{
	char			*name;
	uint8_t			code;
	uint8_t			ar_num;
	t_bool			types_byte;
	uint8_t			types[3];
	uint32_t		cycles;
	t_bool			carry;
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

#endif