/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:35:07 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/17 16:35:10 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			byebye_our_darling(t_vm *v)
{
	int			i;
	t_carr		*cur;
	t_carr		*del;

	i = 0;
	while (i < v->champs_num)
		ft_memdel((void **)&v->champs[i++]);
	cur = v->carrs;
	while (cur)
	{
		del = cur;
		cur = cur->nxt;
		ft_memdel((void **)&del);
	}
	v->carrs = NULL;
	ft_memdel((void **)&v);
}

void			vm_error(char *msg)
{
	ft_printf("{red}{b}ERROR: ");
	if (errno == 0)
		ft_putendl_fd(msg, 2);
	else
		perror(msg);
	ft_printf("{0}");
		// printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		//
		// system("leaks -q corewar");		//
	exit(1);
}
