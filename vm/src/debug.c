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
