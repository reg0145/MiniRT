/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:46:37 by nheo              #+#    #+#             */
/*   Updated: 2021/11/22 15:42:37 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i + 1 < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (n != 0)
		dst[i] = 0;
	return (ft_strlen(src));
}
