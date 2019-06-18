/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 20:59:29 by evlasov           #+#    #+#             */
/*   Updated: 2019/02/01 20:59:30 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    code_separ(t_asm *st, int count)
{
    int     i;

    i = 0;
    while (st->list[count][i])
    {
        if(st->list[count][i] == SEPARATOR_CHAR)
            st->list[count][i] = ' ';
        i++;
    }
}

void    code_space(t_asm *st, int count)
{
    int     i;
    int     k;

    k = 0;
    i = 0;
    char    *tmp;
    tmp = (char*)ft_memalloc((sizeof(char) * (ft_strlen(st->list[count]) + 3)));
    while (st->list[count][i])
    {
//        ft_printf("%c\n", st->list[count][i]);
        if (check_space(st->list[count][i]) == 0)
        {
            while (check_space(st->list[count][i]) != 1
            && (st->list[count][i] != LABEL_CHAR ||
            (st->list[count][i] == LABEL_CHAR && st->list[count][i - 1] == '%'))
            && st->list[count][i] != DIRECT_CHAR
            && st->list[count][i] != '\0')
                tmp[k++] = st->list[count][i++];
            if (st->list[count][i] == LABEL_CHAR)
            {
                ft_printf("LABEL\n");
                tmp[k++] = st->list[count][i++];
                tmp[k++] = ' ';
            }
            if (st->list[count][i] == DIRECT_CHAR)
            {
                ft_printf("DIRECT\n");
                if (tmp[k - 1] != ' ')
                    tmp[k++] = ' ';
                tmp[k++] = st->list[count][i];
            }
            else if (tmp[k - 1] != ' ' && tmp[k - 1] != ',')
                tmp[k++] = ' ';
        }
        i++;
    }
    tmp[k++] = '\n';
    tmp[k] = '\0';
    free(st->list[count]);
    st->list[count] = ft_strdup(tmp);
    free(tmp);
}

void     code_format(t_asm *st)
{
    int     count;

    count = 0;
    while (count < st->str_count && st->list[count][0] == '\n')
        count++;
    ft_printf("code1 = %s\n", st->list[count]);
    while (count < st->str_count)
    {
        code_space(st, count);
        code_separ(st, count);
        count++;
    }
}

