/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:03:30 by nheo              #+#    #+#             */
/*   Updated: 2021/11/20 20:04:56 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	ptr = *lst;
	if (!lst || !new)
		return ;
	if (ptr)
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
	else
		*lst = new;
}
