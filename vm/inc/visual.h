/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anerus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:46:39 by anerus            #+#    #+#             */
/*   Updated: 2019/05/22 19:47:28 by anerus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "vm.h"

int		interface(WINDOW *menu, int yMax, int xMax, t_vm *v);
void	create_border(t_vm *v);
void	del_win(WINDOW *game, WINDOW *info);
void	car_loop(t_vm *v, WINDOW *game, WINDOW *info);

void	*animation(WINDOW *picture);
void	*inter_loop(WINDOW *menu, int yMax, int xMax, t_vm *v);
void	start_menu(t_vm *v);
void	screen_and_color(void);
void	core_img(WINDOW *core, int yMax, int xMax);
void	winner(t_vm *v);
void	print_players(t_vm *v);
void	dash_line(t_vm *v);

#endif
