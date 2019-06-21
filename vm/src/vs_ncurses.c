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

#include "../inc/vm.h"

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
	init_pair(10, COLOR_WHITE, COLOR_RED);
	init_pair(20, COLOR_WHITE, COLOR_GREEN);
	init_pair(30, COLOR_WHITE, COLOR_YELLOW);
	init_pair(40, COLOR_WHITE, COLOR_BLUE);
}
