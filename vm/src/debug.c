/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:41:58 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/21 16:41:59 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			print_carriages(t_vm *v)
{
	t_carr		*cur;

	printf("\n[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]][][][][]\n");
	cur = v->carrs;
	while (cur)
	{
		printf("> id:		%d\n", cur->id);
		printf("> champ:	#%d \"%s\"\n", cur->champ->num, cur->champ->name);
		printf("> pos:		%d\n", cur->pos);
		printf("> op:		%.2x\n", cur->op);
		printf("> wait_cycles:	%d\n", cur->wait_cycles);
		printf("> step:		%u\n", cur->step);
		printf("> last live:	%zu\n", cur->last_live);
		printf("> carry:	%d\n", cur->carry);
		printf("REGS:\n");
		for (int i = 0; i < REG_NUMBER; i++)
		{
			printf("#%02d[%2d] ", i, cur->reg[i]);
			if (i + 1 == REG_NUMBER / 2)
				printf("\n");
		}
		printf("\n[-----------------------------]\n");
		cur = cur->nxt;
	}
}

void			print_champs(t_vm *v)
{
	int			j;

	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	j = 0;
	while (v->champs[j])
	{
		printf("> num: %d\n", v->champs[j]->num);
		printf("> name: %s\n", v->champs[j]->name);
		printf("> comment: %s\n", v->champs[j]->comment);
		printf("> size: %d\n", v->champs[j]->size);
		printf("	EXEC_CODE:\n");
		for (unsigned int i = 1; i <= v->champs[j]->size; i++)
		{
			printf("%.2x", v->champs[j]->code[i - 1]);
			if (i % 2 == 0)
				printf(" ");
			if (i % 16 == 0)
				printf("\n");
		}
		printf("\n-------------------\n");
		j++;
	}
}
