/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:16:34 by nheo              #+#    #+#             */
/*   Updated: 2021/11/29 15:40:53 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == ' ' || c == '\r')
		return (1);
	return (0);
}

static int	ft_check_flow(long long num, int c, int minus)
{
	num *= minus;
	c -= '0';
	if (minus == 1)
		if (num * 10 + c < num)
			return (1);
	if (minus == -1)
		if (num * 10 - c > num)
			return (2);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long		num;
	int				minus;
	int				result;

	num = 0;
	minus = 1;
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= (-1);
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		if (ft_check_flow(num, *str, minus))
			return (ft_check_flow(num, *str, minus) - 2);
		num *= 10;
		num += *str - '0';
		str++;
	}
	result = (int)(num * minus);
	return (result);
}
