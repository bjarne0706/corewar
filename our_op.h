/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:54:46 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/22 09:45:51 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUR_OP_H
# define OUR_OP_H

# include "op.h"
# include <stdint.h>

typedef struct		s_op
{
	char			*name;
	long			code;
	long			arg_count;
	long			argums[3];
	long			cycles;
	int				arg_code_type;
	u_int8_t		t_dir_size;
}					t_op;

static	t_op	g_op_tab[17] =
{
	{"live", 0x01, 1, {T_DIR}, 10, 0, 4},
	{"ld", 0x02, 2, {T_DIR | T_IND, T_REG}, 5, 1, 4},
	{"st", 0x03, 2, {T_REG, T_IND | T_REG}, 5, 1, 4},
	{"add", 0x04, 3, {T_REG, T_REG, T_REG}, 10, 1, 4},
	{"sub", 0x05, 3, {T_REG, T_REG, T_REG}, 10, 1, 4},
	{"and", 0x06, 3,
		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 0x07, 3,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"xor", 0x08, 3,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"zjmp", 0x09, 1, {T_DIR}, 20, 0, 2},
	{"ldi", 0x0a, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2},
	{"sti", 0x0b, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2},
	{"fork", 0x0c, 1, {T_DIR}, 800, 0, 2},
	{"lld", 0x0d, 2, {T_DIR | T_IND, T_REG}, 10, 1, 4},
	{"lldi", 0x0e, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2},
	{"lfork", 0x0f, 1, {T_DIR}, 1000, 0, 2},
	{"aff", 0x10, 1, {T_REG}, 2, 1, 4},
	{0, 0, 0, {0}, 0, 0, 0}
};
#endif
