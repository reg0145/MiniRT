/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:17:37 by nheo              #+#    #+#             */
/*   Updated: 2021/11/24 18:28:53 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (!s1)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && i < len)
		i++;
	while (ft_strchr(set, s1[len - 1]) && len > i)
		len--;
	ptr = ft_calloc(len - i + 1, sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1 + i, len - i + 1);
	return (ptr);
}
