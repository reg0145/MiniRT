/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:10:51 by nheo              #+#    #+#             */
/*   Updated: 2021/11/24 14:52:53 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*ptr;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (0);
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	return (ptr);
}
