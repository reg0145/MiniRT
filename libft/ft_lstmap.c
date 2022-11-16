/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <neho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:13:30 by nheo              #+#    #+#             */
/*   Updated: 2021/11/25 10:13:31 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	new = 0;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp)
		{
			ft_lstadd_back(&new, temp);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&new, del);
			return (0);
		}
	}
	return (new);
}
