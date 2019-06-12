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

void start_menu(void)
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
	inter_loop(menu, yMax, xMax);
    endwin();
}

void	*inter_loop(WINDOW *menu, int yMax, int xMax)
{
    int	prot;
    prot = 1;
	while (1 && prot != 0)
    {
    	prot = interface(menu, yMax, xMax);
    	refresh();
		wrefresh(menu);
    }
    return (NULL);
}

int	interface(WINDOW *menu, int yMax, int xMax)
{
	const char *choices[] = {"Start", "Authors", "Exit"};
	static int	highlight;
	int	i;
	int	key;

	i = -1;
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
	if (key == KEY_UP)
	{
		highlight--;
		if (highlight == -1)
			highlight = 0;
	}
	else if (key == KEY_DOWN)
	{
		highlight++;
			if (highlight == 3)
		highlight = 2;
	}
	else if (key == 10 && highlight == 2)
		return (0);
	else if (key == 10 && highlight == 0)
	{
		start_game(menu, yMax, xMax);
		return (0);
	}
	return (1);
}

void	start_game(WINDOW *game, int yMax, int xMax)
{
	wclear(game);
	wrefresh(game);
	mvwin(game, 0, 0);
	wresize(game, yMax - yMax / 4, xMax - xMax / 4);
	WINDOW *info = newwin(yMax  - yMax / 4, xMax - xMax * 0.75, 0, xMax - xMax * 0.25);
    wattron(info, COLOR_PAIR(1));
    wattron(game, COLOR_PAIR(1));

	box(game, 0, 0);
	// wprintw(game, "%.2x", );
	box(info, 0, 0);
	wattroff(info, COLOR_PAIR(1));
	wattroff(game, COLOR_PAIR(1));

wrefresh(game);
wrefresh(info);


	getch();// before it gets char it refresh the screen

}

