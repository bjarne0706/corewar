/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:04:51 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/23 19:04:53 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			print_arena(t_vm *v, char flag)
{
	int		x;
	int		y;
	int		format;

	format = (flag == 'd' || flag == 's') ? 32 : 64;
	y = 0;
	while (y * format < MEM_SIZE)
	{
		x = 0;
		ft_printf("%06p : ", y * format);
		while (x < format)
		{
			ft_printf("%.2x ", v->arena[y * format + x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void			introduce_champs(t_vm *v)
{
	int		n;

	ft_printf("	{b}{I} Meet the gloriuos champions! {0}\n");
	n = 1;
	while (n <= v->champs_num)
	{
		ft_printf("#%d [%d bytes] {b}%s{0}: {i}\"%s\"{0}\n",
				n, 
				v->champs[n - 1]->size,
				v->champs[n - 1]->name,
				v->champs[n - 1]->comment);
		n++;
	}
}

void			print_usage(void)
{
	ft_printf("{b}{yellow}{u}USAGE:{0}\n");
	ft_printf("	{yellow}./corewar [-d N -s N] [-v] <[-n N]");
	ft_printf(" champ1.cor> <[-n N] champ2.cor> <...>{-}\n");
	ft_printf("\n{u}{b}FLAGS:\n{0}");
	ft_printf("	{b}-d N (-dump N){0}	: ");
	ft_printf("Dump memory (32 octets/line) after N cycles then exit\n");
	ft_printf("	{b}-D N{0}		: ");
	ft_printf("Dump memory (64 octets/line) after N cycles then exit\n");
	ft_printf("	{b}-s N{0}	: Run N cycles, ");
	ft_printf("dump memory (32 octets/line), pause, then repeat\n");
	ft_printf("	{b}-S N{0}	: Run N cycles, ");
	ft_printf("dump memory (64 octets/line), pause, then repeat\n");
	ft_printf("	{b}-v{0}	: Visual mode\n");
	ft_printf("	{b}-n N{0}	: Specify player's number ");
	ft_printf("(0 < N <= number_of_players (%d max))\n", MAX_PLAYERS);
//		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
//		system("leaks -q corewar");		//
	exit(1);
}
