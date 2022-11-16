/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <neho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:14:35 by nheo              #+#    #+#             */
/*   Updated: 2021/12/06 20:49:50 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr1;

	len = ft_strlen(s1) + 1;
	ptr1 = ft_calloc(len, sizeof(char));
	if (!ptr1)
		return (0);
	ft_strlcpy(ptr1, s1, len);
	return ((char *)ptr1);
}
