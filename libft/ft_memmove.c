/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:10:43 by nheo              #+#    #+#             */
/*   Updated: 2021/11/22 14:32:36 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	if (!dst && !src)
		return (0);
	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	if (dst_p < src_p)
		dst = ft_memcpy(dst, src, n);
	else
		while (n)
		{
			dst_p[n - 1] = src_p[n - 1];
			n--;
		}
	return (dst);
}
