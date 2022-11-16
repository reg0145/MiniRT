/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:14:45 by nheo              #+#    #+#             */
/*   Updated: 2021/11/22 19:57:36 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*src_p;

	src_p = (unsigned char *)src;
	while (n)
	{
		if (*src_p == (unsigned char)c)
			return ((void *)src_p);
		src_p++;
		n--;
	}
	return (0);
}
