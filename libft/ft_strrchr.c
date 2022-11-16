/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:13:41 by nheo              #+#    #+#             */
/*   Updated: 2021/11/25 10:27:58 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t			len;
	unsigned char	value;

	len = ft_strlen(str);
	value = (unsigned char)c;
	if (c == 0)
		return ((char *)&str[len]);
	while (len)
	{
		if (str[len - 1] == value)
			return ((char *)&str[len - 1]);
		len--;
	}
	return (0);
}
