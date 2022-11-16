/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:58:12 by nheo              #+#    #+#             */
/*   Updated: 2021/11/24 14:50:48 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = ft_calloc(len, sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcat(ptr, s1, ft_strlen(s1) + 1);
	ft_strlcat(ptr, s2, len);
	return (ptr);
}
