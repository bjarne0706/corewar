/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:54:46 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/18 17:54:48 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm/asm.h"
#include "op.h"

t_op    op_tab[17] =
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
