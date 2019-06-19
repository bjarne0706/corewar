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

void			update_options(t_vm *v)
{
	if (v->options[2] == 'v')
	{
		ft_bzero(v->options, 5);
		v->log = 0;
		v->options[2] = 'v';
	}
}

void			hail_the_hero(t_vm *v)
{
	ft_printf("{magenta}Player {b}%d{0} ", v->last_standing->num);
	ft_printf("{magenta}({b}%s{0}{magenta}) won!{0}\n", v->last_standing->name);
	winner(v);
}

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
	ft_printf("	{yellow}./corewar [-d N] [-s N] [-e / -E] [-v] [-l N]");
	ft_printf(" <[-n N] champ1.cor> <...>{-}\n");
	ft_printf("\n{u}{b}FLAGS:\n{0}");
	ft_printf("	{b}-n N{0}	: Specify player's number ");
	ft_printf("(N >= 1 && N <= number_of_players (%d max)){0}\n", MAX_PLAYERS);
	ft_printf("\n	{b}-v{0}	: Visual mode (overrides dumps and logs)\n\n");
	ft_printf("	{b}-d N (-dump N){0}	: ");
	ft_printf("Dump memory (32 octets/line) after N cycles then exit\n");
	ft_printf("	{b}-D N{0}		: ");
	ft_printf("same as -d but 64 octets/line\n");
	ft_printf("	{b}-s N{0}	: Run N cycles, ");
	ft_printf("dump memory (32 octets/line), pause, then repeat\n");
	ft_printf("	{b}-S N{0}	: ");
	ft_printf("same as -s but 64 octets/line\n");
	ft_printf("	{b}-e / -E{0}	: Dump memory at the end of a game ");
	ft_printf("(32 / 64 octets)\n\n");
	ft_printf("	{b}-a{0}	: Print output of 'aff' operation\n\n");
	ft_printf("	{b}-l N{0}	: ");
	ft_printf("Print logs. Add numbers together to enable several logs:\n");
	ft_printf("\t\t\t{b}1{0} - show lives\n\t\t\t{b}2{0} - show cycles\n");
	ft_printf("\t\t\t{b}4{0} - show operations\n\t\t\t{b}8{0} - show deaths\n");
	ft_printf("\t\t\t{b}16{0} - show PC movements (except for jumps)\n");
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
		system("leaks -q corewar");		//
	exit(1);
}
