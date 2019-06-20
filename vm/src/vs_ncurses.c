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
	v->info = newwin(65, 100, 0, 197);
	v->game = newwin(65, 197, 0, 0);
	WINDOW *help = newwin(6, 197, 66, 0);

    wattron(v->info, COLOR_PAIR(9));
    wattron(v->game, COLOR_PAIR(9));
	box(v->game, 0, 0);
	box(v->info, 0, 0);
	box(help, 0, 0);

	wattroff(v->info, COLOR_PAIR(9));
	wattroff(v->game, COLOR_PAIR(9));
	mvwprintw(help, 1, 15, "SPEED 1");
	mvwprintw(help, 1, 30, "SPEED 2");
	mvwprintw(help, 1, 45, "SPEED 3");

	wrefresh(v->info);
	wrefresh(v->game);
	wrefresh(help);
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

				if (tmp->pc == i && !prot)
				{
					wattron(game, COLOR_PAIR(tmp->champ->num + 4));
					prot = 1;
				}
				tmp = tmp->nxt;
			}
			if (!prot && v->colors[i].champ_num != 0)
				wattron(game, COLOR_PAIR(v->colors[i].champ_num));
			if (--(v->colors[i].st_wait) > 0)
				wattron(game, A_BOLD);
			if (--(v->colors[i].live_wait) > 0)
				wattron(game, COLOR_PAIR(v->colors[i].champ_num * 10));
			mvwprintw(game, y + 1, x + 2,  "%02x", v->arena[i]);
			if (v->colors[i].st_wait > 0)
				wattroff(game, A_BOLD);
			if ((v->colors[i].live_wait) > 0)
				wattron(game, COLOR_PAIR(v->colors[i].champ_num * 10));
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
	wattron(info, A_BOLD);
	mvwprintw(info, 21, 1, "CYCLES TOTAL  % 24d", v->cycles);
	mvwprintw(info, 23, 1, "CYCLES SINCE CHECK  % 18d", v->cyc_since_check);
	mvwprintw(info, 25, 1, "ACTIVE PROCESSES  % 20d", v->carrs_num);
	mvwprintw(info, 27, 1, "CYCLES TO DIE  % 23d", v->cyc_to_die);
	mvwprintw(info, 29, 1, "CYCLES DELTA  % 24d", CYCLE_DELTA);
	mvwprintw(info, 31, 1, "LIVES SINCE CHECK  % 14d / %d", v->lives_since_check, NBR_LIVE);
	mvwprintw(info, 33, 1, "CHECKS DONE  % 20d / %d", v->checks_done, MAX_CHECKS);
	mvwprintw(info, 35, 1, "LAST STANDING % 24s", v->last_standing->name);
	wattroff(info, A_BOLD);
	///////////////////////players
	// mvwprintw(info, 1, 1, "%s", v->last_standing->num, v->last_standing->name);
	print_players(v);
	dash_line(v);






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
	if (get_int == 49)
		v->speed = 0;
	if (get_int == 50)
		v->speed = 50;
	if (get_int == 51)
		v->speed = 100;
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

void	dash_line(t_vm *v)
{
	double	divide;
	int		i;
	int		j;

	i = -1;
	j = 1;
	divide = v->lives_since_check / 50;
	while (++i < v->champs_num)
	{
			// mvwprintw(v->info, 45, j++, "%d", v->champs[i]->current_lives);
		if (divide != 0)
			v->champs[i]->dashes = (double)v->champs[i]->current_lives / divide;
		wattron(v->info, COLOR_PAIR(i + 1));
		while (v->champs[i]->dashes)
		{
			if (j < 50)
				mvwprintw(v->info, 45, j++, "-");
			v->champs[i]->dashes--;
		}
		wattroff(v->info, COLOR_PAIR(i + 1));
	}
	while (j < 49)
		mvwprintw(v->info, 45, j++, "-");



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
		mvwprintw(v->info, id + i, 1, "%s :", v->champs[i]->name);
			mvwprintw(v->info, id + 1 + i, 5, "last_live_cyc % 20d", v->champs[i]->last_live_cyc);
			mvwprintw(v->info, id + 2 + i, 5, "current_lives % 20d", v->champs[i]->current_lives);
			mvwprintw(v->info, id + 3 + i, 5, "prev_lives % 23d", v->champs[i]->prev_lives);
		wattroff(v->info, A_BOLD | COLOR_PAIR(i + 1));
		id += 4;
	}
}

void	winner(t_vm *v)
{
	screen_and_color();
    //get screen size
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);
    init_pair(69, COLOR_WHITE, COLOR_WHITE);
    init_pair(70, COLOR_BLACK, COLOR_BLACK);

    WINDOW *black = newwin(yMax, xMax, 0, 0);
    // WINDOW *menu = newwin(yMax / 4, xMax / 2, yMax / 4, xMax / 4);
    WINDOW *menu = newwin(17, 90, yMax / 5, xMax / 2.8);
    // WINDOW *menu = newwin(17, 90, 0, 0);
    //for using arrow keys
    keypad(menu, true);
    wattron(black, COLOR_PAIR(70));
    wattroff(black, COLOR_PAIR(70));
    wrefresh(black);
	core_img(menu, yMax, xMax);
    wattron(menu, COLOR_PAIR(69));
	box(menu, 0,0);
	wattroff(menu, COLOR_PAIR(69));
    wattron(menu, COLOR_PAIR(v->last_standing->num));
	mvwprintw(menu, 12, 43, "%s", v->last_standing->name);
    wattroff(menu, COLOR_PAIR(v->last_standing->num));
    wrefresh(menu);
    while (1)
    	if (getch() == 27)
    	{
    		endwin();
    		exit(1);
    	}
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
    ///////////////////////live and st
    init_pair(10, COLOR_WHITE, COLOR_RED);
    init_pair(20, COLOR_WHITE, COLOR_GREEN);
    init_pair(30, COLOR_WHITE, COLOR_YELLOW);
    init_pair(40, COLOR_WHITE, COLOR_BLUE);

}
