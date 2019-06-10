/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_players2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:12:51 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/21 17:12:55 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void				rearrange_champs(t_vm *v)
{
	t_champ		*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < v->champs_num - 1)
	{
		j = i + 1;
		while (j < v->champs_num)
		{
			if (v->champs[i]->num > v->champs[j]->num)
			{
				tmp = v->champs[i];
				v->champs[i] = v->champs[j];
				v->champs[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void				validate_champ_nums(t_vm *v)
{
	int		i;

	i = 0;
	while (v->champs[i])
	{
		if (v->champs[i]->num > v->champs_num)
			vm_error("Player's number is higher than total number of players");
		i++;
	}
}

void				assign_champ_nums(t_vm *v)
{
	int		n;
	int		i;

	validate_champ_nums(v);
	n = 1;
	while (n <= v->champs_num)
	{
		while (find_champ(v, n))
			n++;
		i = 0;
		while (i < v->champs_num)
		{
			if (v->champs[i]->num == 0)
			{
				v->champs[i]->num = n++;
				break ;
			}
			i++;
		}
	}
	rearrange_champs(v);
	v->last_standing = v->champs[v->champs_num - 1];
		ft_printf("{lightgray}INIT LAST STANDING: %d. %s{0}\n", v->last_standing->num, v->last_standing->name);		//
}

void				parse_size_and_comment(int fd, t_champ *ch)
{
	unsigned int	null_check;
	int				actual_size;

	if ((read(fd, &ch->size, 4) < 4))
		vm_error("Invalid file (exec code size declaration)");
	ch->size = reverse_byte(ch->size);
//			printf("> size: %d\n", ch->size);		//
	if (ch->size == 0 || ch->size > CHAMP_MAX_SIZE)
		vm_error("Invalid file (exec code size declaration)");
	if (read(fd, &ch->comment, COMMENT_LENGTH) < COMMENT_LENGTH)
		vm_error("Invalid file (comment)");
//		printf("> comment: %s\n", ch->comment);
	null_check = 0;
	if ((read(fd, &null_check, 4) < 4) || null_check != 0)
		vm_error("Invalid file (NULL-delimiter)");
	actual_size = 0;
	actual_size = read(fd, &ch->code, CHAMP_MAX_SIZE);
//		printf("> actual_size: %u\n", actual_size);		//
	if (actual_size <= 0 || (unsigned int)actual_size != ch->size ||
		(read(fd, &null_check, 1) != 0))
		vm_error("Invalid file (exec code actual size)");
/*	for (int i = 1; i <= actual_size; i++)
	{
		printf("%.2x", ch->code[i - 1]);		//
		if (i % 2 == 0)
			printf(" ");
		if (i % 16 == 0)
			printf("\n");
	}
*///	printf("\n");			///
}
int				parse_name(int fd, t_champ *ch)
{
	unsigned int	null_check;

	if (read(fd, &ch->name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (false);
//		printf("> name: %s\n", ch->name);		//
	null_check = 0;
	if ((read(fd, &null_check, 4) < 4) || null_check != 0)
		return (false);
//		printf("null: %#x\n", null_check);	//
	return (true);

}
