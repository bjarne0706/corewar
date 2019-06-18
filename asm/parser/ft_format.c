/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlasov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:21:54 by evlasov           #+#    #+#             */
/*   Updated: 2019/01/29 20:21:56 by evlasov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    err_cmd_string(t_asm *st)
{
    if (st->name == NULL)
        st->err = 1;
    else if (st->comment == NULL)
        st->err = 2;
    else
        st->err = -100;
}

int    save_cmd_string(t_asm *st, int i, int command)
{
    char    *tmp;

    while (check_space(st->str[i]) == 1)
        i++;
    if (st->str[i] == '"')
        i++;
    tmp = ft_cutsword(st->str, "\"", i);
    if (command == 1)
        st->name = tmp;
    else
        st->comment = tmp;
    return (i + ft_strlen(tmp));
}

int     check_cmd_string(t_asm *st, int i)
{
    char    *tmp;

    tmp = ft_cutsword(st->str, "\" \t\v\f\r",i);
    if (ft_strequ(tmp, NAME_CMD_STRING) != 0)
    {
        if (!st->name)
            i = save_cmd_string(st, i + ft_strlen(tmp), 1);
        else
            st->err = -1;
    }
    else if (ft_strequ(tmp, COMMENT_CMD_STRING) != 0)
    {
        if (!st->comment)
            i = save_cmd_string(st, i + ft_strlen(tmp), 2);
        else
            st->err = -2;
    }
    else
        st->err = 3;
    return (i);
}

int    cmd_string(t_asm *st)
{
    int     i;
    int     tmp;

    i = 0;
    while (st->str[i] && st->err == 0)
    {
        tmp = 0;
        if (st->str[i] == COMMENT_CHAR && st->str[i] == ALT_COMMENT_CHAR)
            while (st->str[i] && st->str[i] != '\n')
                i++;
        else if (check_space(st->str[i]) == 0 && st->str[i] != '.' && st->str[i] != '\n')
            err_cmd_string(st);
        else if (st->str[i] == '.')
        {
            tmp = check_cmd_string(st, i);
            if ( tmp < 0)
                st->err = tmp;
            else
                i = tmp;
        }
        i++;
    }
    return (i);
}

void    ft_format(t_asm *st)
{
    int     i;
    int     k;

    k = 0;
    st->err = 0;
    if ((ft_strstr(st->str, NAME_CMD_STRING)) == 0)
        st->err = 1;
    else if ((ft_strstr(st->str, COMMENT_CMD_STRING)) == 0)
        st->err = 2;
    else
        {
            i = cmd_string(st);
            if (st->err == -100)
                st->err = 0;
            while (k < i)
            {
                if (st->str[k] != '\n')
                {
                    if (k == 0 || st->str[k - 1] == '\n')
                        st->str[k] = COMMENT_CHAR;
                    else
                        st->str[k] = ' ';
                }
                k++;
            }
        }
    ft_printf("error = %i\n", st->err);
    if (st->err == 0)
    {
        ft_printf("name = %s\n", st->name);
        ft_printf("comment = %s\n", st->comment);
    }
}
