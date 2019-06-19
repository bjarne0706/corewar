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

void	core_img(WINDOW *core, int yMax, int xMax)
{
	int i;
	const char *str[] = {"  /$$$$$$\n",
" /$$__  $$\n",
"| $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$  /$$  /$$  /$$  /$$$$$$   /$$$$$$\n",
"| $$       /$$__  $$ /$$__  $$ /$$__  $$| $$ | $$ | $$ |____  $$ /$$__  $$\n",
"| $$      | $$  \\ $$| $$  \\__/| $$$$$$$$| $$ | $$ | $$  /$$$$$$$| $$  \\__/\n",
"| $$    $$| $$  | $$| $$      | $$_____/| $$ | $$ | $$ /$$__  $$| $$\n",
"|  $$$$$$/|  $$$$$$/| $$      |  $$$$$$$|  $$$$$/$$$$/|  $$$$$$$| $$\n",
" \\______/  \\______/ |__/       \\_______/ \\_____/\\___/  \\_______/|__/\n", NULL};
	// wprintw(core, str);
	yMax = 0;/////////////////////need to del
	xMax = 0;
	i = -1;
	while (str[++i] != NULL)
		mvwprintw(core, i + 2, 7, str[i]);

}

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
    init_pair(2, COLOR_BLACK, COLOR_BLACK);

    WINDOW *black = newwin(yMax, xMax, 0, 0);
    // WINDOW *menu = newwin(yMax / 4, xMax / 2, yMax / 4, xMax / 4);
    WINDOW *menu = newwin(17, 90, yMax / 5, xMax / 2.8);
    // WINDOW *menu = newwin(17, 90, 0, 0);

    //for using arrow keys
    keypad(menu, true);
    wattron(black, COLOR_PAIR(2));
    wattroff(black, COLOR_PAIR(2));
    wrefresh(black);

	core_img(menu, yMax, xMax);

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
	yMax = 0;
	xMax = 0;//////////ned to del
	const char *choices[] = {"START", "AUTHORS", "EXIT"};
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
		mvwprintw(menu, i + 11, 43, &*choices[i]);
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
	system("afplay sounds/Megalovania.mp3 &> /dev/null &");
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
	while (++y < 63)
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
			if (!prot && v->colors[i].champ_num != 0)
				wattron(game, COLOR_PAIR(v->colors[i].champ_num));
			mvwprintw(game, y + 1, x + 2,  "%02x", v->arena[i]);
			x += 2;
			if (!prot && v->colors[i].champ_num != 0)
				wattroff(game, COLOR_PAIR(v->colors[i].champ_num));
			wattroff(game, COLOR_PAIR(5));
			wattroff(game, COLOR_PAIR(6));
			wattroff(game, COLOR_PAIR(7));
			wattroff(game, COLOR_PAIR(8));
			mvwprintw(game, y + 1, x + 2,  " ", v->arena[i]);

			i++;
			x += 1;
		}
	}
	mvwprintw(info, 1, 1, "CYCLES TOTAL = %d", v->cycles);
	mvwprintw(info, 2, 1, "CYCLES SINCE CHECK = %d", v->cyc_since_check);
	mvwprintw(info, 3, 1, "ACTIVE PROCESSES = %d", v->carrs_num);
	mvwprintw(info, 4, 1, "CYCLES TO DIE = % 9d", v->cyc_to_die);
	mvwprintw(info, 5, 1, "CYCLES DELTA = %d", CYCLE_DELTA);
	mvwprintw(info, 6, 1, "LIVES SINCE CHECK = % 5d / %d", v->lives_since_check, NBR_LIVE);
	mvwprintw(info, 7, 1, "CHECKS DONE = %d / %d", v->checks_done, MAX_CHECKS);
	mvwprintw(info, 8, 1, "LAST STANDING = %d \"%s\"", v->last_standing->num, v->last_standing->name);





	box(v->game, 0, 0);
	box(v->info, 0, 0);
	refresh();
	wrefresh(game);
	wrefresh(info);

	int get_int;
	nodelay(stdscr, TRUE);
	get_int = getch();
	int	stop_music;
	stop_music = 0;
	if (get_int == 27)
	{
		del_win(game, info);
		exit (1);
	}
	if (get_int == 32)
	{
		system("pkill -STOP afplay");
		stop_music++;
		get_int = 0;
		while (get_int != 32)
		{
			if (get_int == 27)
			{
				del_win(game, info);
				exit (1);
			}
			get_int = getch();
		}
		system("pkill -CONT afplay");
	}
}

void	winner(t_vm *v)
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
    init_pair(2, COLOR_BLACK, COLOR_BLACK);

    WINDOW *black = newwin(yMax, xMax, 0, 0);
    // WINDOW *menu = newwin(yMax / 4, xMax / 2, yMax / 4, xMax / 4);
    WINDOW *menu = newwin(17, 90, yMax / 5, xMax / 2.8);
    // WINDOW *menu = newwin(17, 90, 0, 0);

    //for using arrow keys
    keypad(menu, true);
    wattron(black, COLOR_PAIR(2));
    wattroff(black, COLOR_PAIR(2));
    wrefresh(black);

	core_img(menu, yMax, xMax);
	mvwprintw(menu, 12, 43, "%s", v->last_standing->name);


    wattron(menu, COLOR_PAIR(1));
	box(menu, 0,0);
	wattroff(menu, COLOR_PAIR(1));


    wrefresh(menu);
    sleep(15);
    endwin();
}

void	del_win(WINDOW *game, WINDOW *info)
{
	delwin(game);
	delwin(info);
	endwin();
	system("pkill afplay");
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
