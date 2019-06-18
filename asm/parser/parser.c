/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:04:51 by evlasov           #+#    #+#             */
/*   Updated: 2019/01/12 19:04:52 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     add_com(int count, char *str, t_asm *st)
{
    char    *tmp;
    int     i;

    i = 0;
    tmp = NULL;
    tmp = ft_cutword(str, i);
    if (tmp != NULL)
    {
        //
        //
        //
        //
        //
        //
        //
        i = i + ft_strlen(tmp);
        if (i > 0 && i - ft_strlen(tmp) == 0 && tmp[i - 1] == LABEL_CHAR)
        {

            st->com[count].label = malloc(100);
            st->com[count].label = tmp;
            ft_printf("LBL = %s", st->com[count].label);
        }
    }
    return (0);
}

void     parser(t_asm *st)
{
    int     count;

    count = 0;
    while (count < st->str_count)
    {
        add_com(count, st->list[count], st);
        count++;
    }
    ft_printf("parser %i\n", st->str_count);
}
