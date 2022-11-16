/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:10:20 by nheo              #+#    #+#             */
/*   Updated: 2021/11/24 10:59:04 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;
	size_t			i;

	if (!dst && !src)
		return (0);
	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < num)
	{
		dst_p[i] = src_p[i];
		i++;
	}
	return (dst);
}
