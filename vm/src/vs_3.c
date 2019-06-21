/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:15:32 by anerus            #+#    #+#             */
/*   Updated: 2019/06/21 19:15:34 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	print_and_refresh(t_vm *v)
{
	wattron(v->info, A_BOLD);
	print_and_refresh2(v);
	wattroff(v->info, A_BOLD);
	print_players(v);
	mvwprintw(v->info, 22, 13, "CURRENT LIVES BREAKDOWN");
	mvwprintw(v->info, 25, 10, "PREVIOUS PERIOD LIVES BREAKDOWN");
	dash_line(v);
	dash_line2(v);
	mvwprintw(v->info, 43, 4, "/----------------------------------------\\");
	mvwprintw(v->info, 44, 5, "* Press \"SPACE\" for pause");
	mvwprintw(v->info, 45, 5, "* Press UP/DOWN for choose your speed");
	mvwprintw(v->info, 46, 5, "* Press ESC for exit");
	mvwprintw(v->info, 47, 4, "\\----------------------------------------/");
	box(v->game, 0, 0);
	box(v->info, 0, 0);
	refresh();
	wrefresh(v->game);
	wrefresh(v->info);
}

void	dash_line(t_vm *v)
{
	double	divide;
	int		i;
	int		j;

	i = -1;
	j = 1;
	divide = v->lives_since_check / 50;
	mvwprintw(v->info, 23, j++, "[");
	while (++i < v->champs_num)
	{
		if (divide != 0)
			v->champs[i]->dashes = (double)v->champs[i]->current_lives / divide;
		wattron(v->info, COLOR_PAIR(i + 1));
		while (v->champs[i]->dashes)
		{
			if (j < 50)
				mvwprintw(v->info, 23, j++, "=");
			v->champs[i]->dashes--;
		}
		wattroff(v->info, COLOR_PAIR(i + 1));
	}
	while (j < 50)
		mvwprintw(v->info, 23, j++, "=");
	mvwprintw(v->info, 23, j++, "]");
}

void	dash_line2(t_vm *v)
{
	double	divide;
	int		i;
	int		j;

	i = -1;
	j = 1;
	divide = v->prev_lives / 50;
	mvwprintw(v->info, 26, j++, "[");
	while (++i < v->champs_num)
	{
		if (divide != 0)
			v->champs[i]->dashes = (double)v->champs[i]->prev_lives / divide;
		wattron(v->info, COLOR_PAIR(i + 1));
		while (v->champs[i]->dashes)
		{
			if (j < 50)
				mvwprintw(v->info, 26, j++, "=");
			v->champs[i]->dashes--;
		}
		wattroff(v->info, COLOR_PAIR(i + 1));
	}
	while (j < 50)
		mvwprintw(v->info, 26, j++, "=");
	mvwprintw(v->info, 26, j++, "]");
}

void	print_players(t_vm *v)
{
	int	i;
	int	id;

	i = -1;
	id = 1;
	while (++i < MAX_PLAYERS && v->champs[i])
	{
		wattron(v->info, A_BOLD | COLOR_PAIR(i + 1));
		mvwprintw(v->info, id + i, 4, "%s :",
			v->champs[i]->name);
		mvwprintw(v->info, id + 1 + i, 8, "Current lives: % 22d",
			v->champs[i]->current_lives);
		mvwprintw(v->info, id + 2 + i, 8, "Preveous period lives: % 14d",
			v->champs[i]->prev_lives);
		mvwprintw(v->info, id + 3 + i, 8, "Last live cycle: % 20d",
			v->champs[i]->last_live_cyc);
		wattroff(v->info, A_BOLD | COLOR_PAIR(i + 1));
		id += 4;
	}
}

void	winner(t_vm *v)
{
	wattron(v->info, COLOR_PAIR(v->last_standing->num));
	mvwprintw(v->info, 55, 11, "Player %d (%s) won!",
		v->last_standing->num, v->last_standing->name);
	wattroff(v->info, COLOR_PAIR(v->last_standing->num));
	wrefresh(v->info);
	while (1)
		if (getch() == 27)
		{
			endwin();
			system("pkill afplay");
			exit(1);
		}
}
