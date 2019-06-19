/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:36:17 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/31 16:36:19 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void		log_op_live(int id, int champ, int arg)
{
	ft_printf("{green}[p%d {i}ch%d\e[23m]> ", id, champ);
	ft_printf("{I}live\e[27m {b}%d{0}\n", arg);
}

static void		log_live(int num, char *name)
{
	ft_printf("{green}A process shows that Player ");
	ft_printf("{b}%d\e[22m ({b}%s\e[22m) is alive{0}\n", num, name);
}

void			op_live(t_vm *v, t_carr *c, t_op *op)
{
	int			arg;
	t_champ		*ch;

	arg = get_int(v, calc_address(c->pc + 1, false, 0), op->t_dir_size);
	c->last_live = v->cycles;
	v->lives_since_check++;
	ch = NULL;
	if (arg < 0 && arg >= -(v->champs_num))
	{
		ch = v->champs[-arg - 1];
		ch->last_live_cyc = v->cycles;
		ch->current_lives++;
		v->last_standing = ch;
		if (v->options[2] == 'v')
		{
			v->colors[c->pc].champ_num = ch->num;
			v->colors[c->pc].live_wait = 50;
		}
		if (v->log & LOG_LIVES)
			log_live(ch->num, ch->name);
	}
	c->step = step_calc(c, op);
	if (v->log & LOG_OPS)
		log_op_live(c->id, c->champ->num, arg);
}
