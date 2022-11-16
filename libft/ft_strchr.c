/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:12:53 by nheo              #+#    #+#             */
/*   Updated: 2021/11/22 20:04:46 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	value;

	i = 0;
	value = (char)c;
	while (str[i])
	{
		if (str[i] == value)
			return ((char *)&str[i]);
		i++;
	}
	if (!value && !str[i])
		return ((char *)&str[i]);
	return (0);
}
