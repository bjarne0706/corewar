/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:33:46 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 13:33:30 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*list2;

	if (!lst)
		return (NULL);
	list2 = f(lst);
	new_lst = list2;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list2->next = f(lst)))
		{
			free(list2->next);
			return (NULL);
		}
		list2 = list2->next;
	}
	return (new_lst);
}
