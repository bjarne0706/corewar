/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:15:18 by anerus            #+#    #+#             */
/*   Updated: 2019/06/21 19:15:20 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	afplay_highl(int *highlight, int value)
{
	system("pkill afplay");
	system("afplay sounds/magic_immune.mp3 &> /dev/null &");
	(*highlight) = value;
}

int		choose_sound(WINDOW *menu, int *highlight, int *key)
{
	if ((*key) == KEY_UP)
	{
		(*highlight)--;
		if ((*highlight) == -1)
			afplay_highl(highlight, 0);
	}
	else if ((*key) == KEY_DOWN)
	{
		(*highlight)++;
		if ((*highlight) == 3)
			afplay_highl(highlight, 2);
	}
	else if ((*key) == 10 && (*highlight) == 2)
	{
		endwin();
		exit(1);
	}
	else if ((*key) == 10 && (*highlight) == 1)
		authors(menu);
	else if ((*key) == 10 && (*highlight) == 0)
	{
		wrefresh(menu);
		return (0);
	}
	return (1);
}

void	authors(WINDOW *menu)
{
	mvwprintw(menu, 12, 10, "anerus");
	mvwprintw(menu, 12, 25, "dstepane");
	mvwprintw(menu, 12, 55, "dchantse");
	mvwprintw(menu, 12, 70, "evlasov");
}

void	create_border(t_vm *v)
{
	screen_and_color();
	v->info = newwin(65, 52, 0, 197);
	v->game = newwin(65, 197, 0, 0);
	wattron(v->info, COLOR_PAIR(9));
	wattron(v->game, COLOR_PAIR(9));
	box(v->game, 0, 0);
	box(v->info, 0, 0);
	wattroff(v->info, COLOR_PAIR(9));
	wattroff(v->game, COLOR_PAIR(9));
	wrefresh(v->info);
	wrefresh(v->game);
	system("afplay sounds/Megalovania.mp3 &> /dev/null &");
}

void	car_loop(t_vm *v)
{
	int		y;
	int		i;

	y = -1;
	i = 0;
	while (++y < 63)
	{
		car_loop_inloop(v, &i, &y);
	}
	print_and_refresh(v);
	car_loop2(v);
}
