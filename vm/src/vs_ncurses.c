/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:07:09 by anerus            #+#    #+#             */
/*   Updated: 2019/06/09 19:44:48 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visual.h"

void start_menu(t_vm *v)
{
    initscr();
    noecho();
    refresh();
    curs_set(0);
    //get screen size
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    WINDOW *menu = newwin(yMax / 4, xMax / 2, yMax / 4, xMax / 4);
    //for using arrow keys
    keypad(menu, true);
    wattron(menu, COLOR_PAIR(1));
	box(menu, 0,0);
	wattroff(menu, COLOR_PAIR(1));
    wrefresh(menu);
    /////////menu interface
	inter_loop(menu, yMax, xMax, v);
	// delwin(menu);
    endwin();
}

void	*inter_loop(WINDOW *menu, int yMax, int xMax, t_vm *v)
{
    int	prot;
    prot = 1;
	while (1 && prot != 0)
    {
    	prot = interface(menu, yMax, xMax, v);
    	refresh();
		wrefresh(menu);
    }
    return (NULL);
}

int	interface(WINDOW *menu, int yMax, int xMax, t_vm *v)
{
	const char *choices[] = {"Start", "Authors", "Exit"};
	static int	highlight;
	int	i;
	int	key;

	i = -1;
	v = NULL;
	// highlight = 0;
	// choices ;
	while (++i < 3)
	{
		if (i == highlight)
			wattron(menu, A_REVERSE);
		mvwprintw(menu, i + yMax / 9, xMax / 4 - 3, &*choices[i]);
		wattroff(menu, A_REVERSE);
	}
	key = wgetch(menu);
	if (key == 10)
	{
		system("pkill afplay");
		system("afplay sounds/button-sound-14.mp3 &> /dev/null &");
	}
	if (key == KEY_UP)
	{
		highlight--;
		if (highlight == -1)
		{
			system("pkill afplay");
			system("afplay sounds/magic_immune.mp3 &> /dev/null &");
			highlight = 0;
		}
	}
	else if (key == KEY_DOWN)
	{
		highlight++;
			if (highlight == 3)
			{
				system("pkill afplay");
				system("afplay sounds/magic_immune.mp3 &> /dev/null &");
				highlight = 2;
			}
	}
	else if (key == 10 && highlight == 2)
	{
    	endwin();
    	exit (1);
	}
	else if (key == 10 && highlight == 0)
	{
		wrefresh(menu);
		return (0);
	}
	return (1);
}

void	create_border(t_vm *v)
{
	// mvwin(game, 0, 0);
	// wresize(game, yMax - yMax / 4, xMax - xMax / 4);
	screen_and_color();
	v->info = newwin(66, 100, 0, 197);
	v->game = newwin(66, 197, 0, 0);

    wattron(v->info, COLOR_PAIR(9));
    wattron(v->game, COLOR_PAIR(9));
	box(v->game, 0, 0);
	box(v->info, 0, 0);
	wattroff(v->info, COLOR_PAIR(9));
	wattroff(v->game, COLOR_PAIR(9));


	wrefresh(v->info);
	wrefresh(v->game);

}

void	car_loop(t_vm *v, WINDOW *game, WINDOW *info)
{
	int		x;
	int		y;
	int		i;
	short	prot;
	t_carr *tmp;

	y = -1;
	i = 0;
	while (++y < 64)
	{
		x = 0;
		while (x < 194)
		{
			prot = 0;
			// mvwprintw(info, 1, 1, "Index = %d", i);
			tmp = v->carrs;
			while (tmp)
			{

				if (tmp->pc == i)
				{
					wattron(game, COLOR_PAIR(tmp->champ->num + 4));
					prot = 1;
				}
				tmp = tmp->nxt;
			}
			if (!prot && v->colors[i] != 0)
				wattron(game, COLOR_PAIR(v->colors[i]));
			mvwprintw(game, y + 1, x + 2,  "%02x", v->arena[i]);
			x += 2;
			if (!prot && v->colors[i] != 0)
				wattroff(game, COLOR_PAIR(v->colors[i]));
			wattroff(game, COLOR_PAIR(5));
			wattroff(game, COLOR_PAIR(6));
			wattroff(game, COLOR_PAIR(7));
			wattroff(game, COLOR_PAIR(8));
			mvwprintw(game, y + 1, x + 2,  " ", v->arena[i]);

			i++;
			x += 1;
		}
	}
	refresh();
	wrefresh(game);
	wrefresh(info);
}

void	del_win(WINDOW *game, WINDOW *info)
{
	delwin(game);
	delwin(info);
	endwin();
}

void	screen_and_color(void)
{
	initscr();
	noecho();
	refresh();
	curs_set(0);
	start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_YELLOW);
    init_pair(8, COLOR_BLACK, COLOR_BLUE);

}
