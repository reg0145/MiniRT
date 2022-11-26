/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 20:33:13 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 12:44:09 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_numbers(long long n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	num;
	char			*ptr;

	num = (unsigned int)n;
	len = count_numbers(n);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (0);
	if (n < 0)
	{
		ptr[0] = '-';
		num *= -1;
	}
	while (len > 1)
	{
		ptr[len - 1] = '0' + (num % 10);
		num /= 10;
		len--;
	}
	if (ptr[0] != '-')
		ptr[0] = '0' + (num % 10);
	return (ptr);
}
