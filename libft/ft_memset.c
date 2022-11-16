/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:09:04 by nheo              #+#    #+#             */
/*   Updated: 2021/11/22 19:46:14 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t num)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	value;

	i = 0;
	p = (unsigned char *)ptr;
	value = (unsigned char)c;
	while (i < num)
	{
		p[i] = value;
		i++;
	}
	return (ptr);
}
