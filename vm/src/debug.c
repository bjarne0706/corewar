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

void			print_color_map(t_vm *v)
{
	int		x;
	int		y;

	y = 0;
	ft_printf("\n\n");
	while (y * 64 < MEM_SIZE)
	{
		x = 0;
		ft_printf("%06p : ", y * 64);
		while (x < 64)
		{
			ft_printf("%.2x ", v->colors[y * 64 + x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void			print_vm_params(t_vm *v)
{
	ft_printf("\n{_darkgray}{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{VM}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n");
		printf("> Options: ");		//
			for (size_t i = 0; i < sizeof(v->options); i++)	//
					printf("[%c]", v->options[i]);		///
		printf("\n> dump_cycles: %d||%d\n", v->dump_cycles[0], v->dump_cycles[1]);	//
		printf("> champs num: %d\n", v->champs_num);	//
		if (v->last_standing)
			printf("> Last standing: (%d) %s\n", v->last_standing->num, v->last_standing->name);
		printf("> carrs num: %zd\n", v->carrs_num);	//
		printf("> CYCLES PASSED: %zd\n", v->cycles);
		printf("> cycles since check: %zd\n", v->cyc_since_check);
		printf("> lives since check: %zd\n", v->lives_since_check);
		printf("> checks done: %zd\n", v->checks_done);
		printf("> Cycles To Die: %d\n", v->cyc_to_die);
	ft_printf("======================================={_}\n");
}

void			print_carriages(t_vm *v)
{
	t_carr		*cur;

	printf("\n[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]][][][][]\n");
	cur = v->carrs;
	while (cur)
	{
		printf("> id:		%d\n", cur->id);
		printf("> champ:	#%d \"%s\"\n", cur->champ->num, cur->champ->name);
		printf("> pc:		%d\n", cur->pc);
//			cur->op = v->arena[cur->pc];
		printf("> op:		%.2x\n", cur->op);
		printf("> wait_cycles:	%d\n", cur->wait_cycles);
		printf("> args_types:	%d|%d|%d\n", cur->arg_types[0], cur->arg_types[1], cur->arg_types[2]);
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
	while (j < v->champs_num)
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
