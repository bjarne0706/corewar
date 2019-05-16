/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:34:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/05/16 15:34:49 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/libft.h"
# include "../../op.h"

# include <limits.h>	//?
# include <stdio.h>		//TMP

typedef 	enum 
{
	false = 0,
	true = !false
}			t_bool;

typedef struct		s_champ
{
	int				num;
	char			*name;
	char			*comment;

}					t_champ;

typedef struct		s_carr
{
	t_champ			*champ;
	t_bool			carry;

	struct s_carr	*nxt;
}					t_carr;

typedef struct		s_vm
{
	unsigned char	arena[MEM_SIZE];
	t_champ			champs[MAX_PLAYERS];
	t_carr			*carrs;

}					t_vm;


void				print_usage(void);

#endif
