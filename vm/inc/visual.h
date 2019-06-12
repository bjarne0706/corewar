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



int		interface(WINDOW *menu, int yMax, int xMax);
void	start_game(WINDOW *game, int yMax, int xMax);
void	*animation(WINDOW *picture);
void	*inter_loop(WINDOW *menu, int yMax, int xMax);
void	start_menu(void);


#endif
