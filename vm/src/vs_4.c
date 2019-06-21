/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:15:38 by anerus            #+#    #+#             */
/*   Updated: 2019/06/21 19:15:41 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	core_img(WINDOW *core)
{
	const char	*str[] = {"  /$$$$$$\n",
" /$$__  $$\n",
"| $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$  /$$  /$$  /$$  /$$$$$$   /$$$$$$\n",
"| $$       /$$__  $$ /$$__  $$ /$$__  $$| $$ | $$ | $$ |____  $$ /$$__  $$\n",
"| $$      | $$  \\ $$| $$  \\__/| $$$$$$$$| $$ | $$ | $$  /$$$$$$$| $$  \\__/",
"| $$    $$| $$  | $$| $$      | $$_____/| $$ | $$ | $$ /$$__  $$| $$\n",
"|  $$$$$$/|  $$$$$$/| $$      |  $$$$$$$|  $$$$$/$$$$/|  $$$$$$$| $$\n",
" \\______/  \\______/ |__/       \\_______/ \\_____/\\___/  \\_______/|__/\n",
NULL};
	int			i;

	i = -1;
	while (str[++i] != NULL)
		mvwprintw(core, i + 2, 7, str[i]);
}

void	start_menu2(void)
{
	initscr();
	noecho();
	refresh();
	curs_set(0);
	start_color();
}

void	start_menu(t_vm *v)
{
	int		ymax;
	int		xmax;
	WINDOW	*black;
	WINDOW	*menu;

	start_menu2();
	getmaxyx(stdscr, ymax, xmax);
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	black = newwin(ymax, xmax, 0, 0);
	menu = newwin(17, 90, ymax / 5, xmax / 2.8);
	keypad(menu, true);
	wattron(black, COLOR_PAIR(2));
	wattroff(black, COLOR_PAIR(2));
	wrefresh(black);
	core_img(menu);
	wattron(menu, COLOR_PAIR(1));
	box(menu, 0, 0);
	wattroff(menu, COLOR_PAIR(1));
	wrefresh(menu);
	inter_loop(menu, v);
	endwin();
}

void	*inter_loop(WINDOW *menu, t_vm *v)
{
	int	prot;

	prot = 1;
	while (1 && prot != 0)
	{
		prot = interface(menu, v);
		refresh();
		wrefresh(menu);
	}
	return (NULL);
}

int		interface(WINDOW *menu, t_vm *v)
{
	const char	*choices[] = {"START", "AUTHORS", "EXIT"};
	static int	highlight;
	int			i;
	int			key;

	i = -1;
	v = NULL;
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
	if (!choose_sound(menu, &highlight, &key))
		return (0);
	return (1);
}
