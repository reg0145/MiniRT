/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:33:55 by nheo              #+#    #+#             */
/*   Updated: 2021/11/20 15:41:05 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_numbers(unsigned long n, int base)
{
	size_t	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

static char	ft_based_value(unsigned long n, int base)
{
	if (n % base >= 10)
		return (n % base - 10 + 'a');
	else
		return (n % base + '0');
}

char	*ft_based_num_pointer(long n, int base)
{
	size_t			len;
	char			*ptr;
	unsigned long	num;

	num = (unsigned long)n;
	len = count_numbers(num, base);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (0);
	while (len)
	{
		ptr[len - 1] = ft_based_value(num, base);
		num /= base;
		len--;
	}
	return (ptr);
}

char	*ft_based_num(int n, int base)
{
	size_t			len;
	char			*ptr;
	unsigned long	num;

	num = (unsigned int)n;
	len = count_numbers(num, base);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (0);
	while (len)
	{
		ptr[len - 1] = ft_based_value(num, base);
		num /= base;
		len--;
	}
	return (ptr);
}