/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:54:05 by evlasov           #+#    #+#             */
/*   Updated: 2019/01/12 19:54:06 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    rm_comment(t_asm *st, int count, int i)
{
    char    *tmp;

//    if (i > 0)
//        i--;
    while (i > 0 && check_space(st->list[count][i]) == 1)
        i--;
    if (i == 0)
        tmp = ft_strdup("\n");
    else
        tmp = ft_strsub(st->list[count], 0, i);
    ft_strdel(&st->list[count]);
    st->list[count] = ft_strdup(tmp);
    ft_strdel(&tmp);
//    ft_printf("new_c = %i %s\n", count, st->list[count]);
}

void    find_comments(t_asm *st)
{
    int     count;
    int     i;

    count = 0;
    while (count < st->str_count)
    {
//        ft_printf("count = %i %s:\n", count, st->list[count]);
        i = 0;
        while (st->list[count][i] != '\0')
        {
            if ((st->list[count][i] == COMMENT_CHAR)
            || st->list[count][i] == ALT_COMMENT_CHAR)
                rm_comment(st, count, i);
            i++;
        }
        count++;
    }
}

static int	ft_wlen(char const *str, char c, int n)
{
    int		len;

    len = 0;
    while (str[n + len] != c && str[n + len])
        len++;
    return (len);
}

void	split(t_asm *st)
{
    int		i;
    int		j;

    i = 0;
    j = 0;
    if (!(st->list = (char**)malloc(sizeof(char*) * (ft_strlen(st->str) + 1))))
        return;
    while (st->str[i])
    {
        if (st->str[i] == '\n')
        {
            i++;
            if (st->str[i] == '\n')
            {
                st->list[j++] = ft_strdup("\n");
                i++;
            }
        }
        else
        {
            st->list[j++] = ft_strsub(st->str, i, ft_wlen(st->str, '\n', i));
            i = i + ft_wlen(st->str, '\n', i);
        }
    }
    st->list[j] = 0;
}

void    sort(t_asm *st)
{
    ft_format(st);
    split(st);
    find_comments(st);
    code_format(st);
    parser(st);


//    DELME!!!!
    int count = 0;
    while (count < st->str_count)
    {
        ft_printf("%i:%s", count, st->list[count]);
        count++;
    }
//    DELME!!!!
}
