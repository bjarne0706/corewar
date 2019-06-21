/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:15:23 by anerus            #+#    #+#             */
/*   Updated: 2019/06/21 19:15:25 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	car_loop_inloop(t_vm *v, int *i, int *y)
{
	t_carr	*tmp;
	int		x;

	x = 0;
	while (x < 194)
	{
		v->prot = 0;
		tmp = v->carrs;
		while (tmp)
		{
			if (tmp->pc == (*i))
			{
				wattron(v->game, COLOR_PAIR(tmp->champ->num + 4));
				v->prot = 1;
				break ;
			}
			tmp = tmp->nxt;
		}
		print_cars(v, i, &x, y);
	}
}

void	print_cars(t_vm *v, int *i, int *x, int *y)
{
	if (!v->prot && v->colors[(*i)].champ_num != 0)
		wattron(v->game, COLOR_PAIR(v->colors[(*i)].champ_num));
	if (--(v->colors[(*i)].st_wait) > 0)
		wattron(v->game, A_BOLD);
	if (--(v->colors[(*i)].live_wait) > 0)
		wattron(v->game, COLOR_PAIR(v->colors[(*i)].champ_num * 10));
	mvwprintw(v->game, *(y) + 1, *(x) + 2, "%02x", v->arena[(*i)]);
	if (v->colors[(*i)].st_wait > 0)
		wattroff(v->game, A_BOLD);
	if ((v->colors[(*i)].live_wait) > 0)
		wattron(v->game, COLOR_PAIR(v->colors[(*i)].champ_num * 10));
	(*x) += 2;
	if (!v->prot && v->colors[(*i)].champ_num != 0)
		wattroff(v->game, COLOR_PAIR(v->colors[(*i)].champ_num));
	if (v->prot)
	{
		wattroff(v->game, COLOR_PAIR(5));
		wattroff(v->game, COLOR_PAIR(6));
		wattroff(v->game, COLOR_PAIR(7));
		wattroff(v->game, COLOR_PAIR(8));
	}
	mvwprintw(v->game, *(y) + 1, *(x) + 2, " ", v->arena[(*i)]);
	(*i)++;
	(*x) += 1;
}

void	car_loop2(t_vm *v)
{
	int get_int;
	int	stop_music;

	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	get_int = getch();
	stop_music = 0;
	if (get_int == KEY_DOWN && v->speed >= 10)
		v->speed -= 10;
	if (get_int == KEY_UP)
		v->speed += 10;
	if (get_int == 27)
	{
		del_win(v->game, v->info);
		exit(1);
	}
	if (get_int == 32)
		stop_and_cont(v, &stop_music, &get_int);
}

void	stop_and_cont(t_vm *v, int *stop_music, int *get_int)
{
	system("pkill -STOP afplay");
	(*stop_music)++;
	*(get_int) = 0;
	while (*(get_int) != 32)
	{
		if (*(get_int) == 27)
		{
			del_win(v->game, v->info);
			exit(1);
		}
		*(get_int) = getch();
	}
	system("pkill -CONT afplay");
}

void	print_and_refresh2(t_vm *v)
{
	mvwprintw(v->info, 28, 20, "SPEED % 5d", v->speed);
	mvwprintw(v->info, 30, 6, "CYCLES TOTAL  % 25d", v->cycles);
	mvwprintw(v->info, 31, 6, "ACTIVE PROCESSES  % 21d", v->carrs_num);
	mvwprintw(v->info, 33, 6, "CYCLES SINCE CHECK  % 19d", v->cyc_since_check);
	mvwprintw(v->info, 34, 6, "CYCLES TO DIE  % 24d", v->cyc_to_die);
	mvwprintw(v->info, 35, 6, "cycles delta  % 25d", CYCLE_DELTA);
	mvwprintw(v->info, 37, 6, "LIVES SINCE CHECK  % 20d", v->lives_since_check);
	mvwprintw(v->info, 38, 6, "nbr live  % 29d", NBR_LIVE);
	mvwprintw(v->info, 40, 6, "CHECKS DONE  % 26d", v->checks_done);
	mvwprintw(v->info, 41, 6, "max checks  % 27d", MAX_CHECKS);
}
