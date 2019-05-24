/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:07:09 by anerus            #+#    #+#             */
/*   Updated: 2019/05/18 17:05:07 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int main(int argc, char *argv[])
{
    initscr();
    noecho();
    refresh();
    curs_set(0);

    //get screen size
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    //colors
    if (!has_colors())
    {
    	printw("Terminal doesn't support color((");
    	getch();
    	return (-1);
    }
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

	WINDOW *picture = newwin(5, 10, 0, 0);
	//////////////THREAD

	pthread_t	thread_1;
	pthread_t	thread_2;


	pthread_create(&thread_1, NULL, animation(picture), NULL); 


	pthread_create(&thread_2, NULL, inter_loop(menu, yMax, xMax), NULL); 

	//////////////THREAD


    // pthread_join(thread_1, NULL);
	// getch();
    endwin();
    return 0;
}

void	*inter_loop(WINDOW *menu, int yMax, int xMax)
{
    int	prot;
    prot = 1;
	while (1 && prot != 0)
    {
    	// animation(picture);


    	prot = interface(menu, yMax, xMax);
    	refresh();
		wrefresh(menu);
    }
    return (NULL);
}

void	*animation(WINDOW *picture)
{
	static int i;

	if (!i)
		i = 0;
	while (1)
	{
		if (i % 2 == 0)
			wprintw(picture, " \\o/ \n  #  \n_/ \\_ ");
		else if (i % 2 != 0)
			wprintw(picture, "  o  \n /#\\ \n _|_");
		i++;
		wrefresh(picture);
		wclear(picture);
		sleep(1);
	}
	// wgetch(picture);
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
	box(game, 0, 0);
	wgetch(game);// before it gets char it refresh the screen

}

