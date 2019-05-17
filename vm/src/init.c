/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:33:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/17 16:33:49 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

t_vm			*init_vm(void)
{
	t_vm		*v;
	
	if(!(v = (t_vm *)ft_memalloc(sizeof(t_vm))))
		vm_error("VM initialization failed");
	ft_bzero(v->options, 3);
	v->dump_cycles[0] = -1;
	v->dump_cycles[1] = -1;

	return (v);
}