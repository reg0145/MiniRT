/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:43:14 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 12:43:17 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_flow(double num, int c, int minus)
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

static void	check_minus_and_format(char **str, int *minus)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*minus *= (-1);
		(*str)++;
	}
	if (!ft_isdigit(**str))
		ft_error("worng input : type must be double");
}

double	ft_atod(char *str)
{
	double			num;
	int				minus;
	double			result;

	num = 0;
	result = 0;
	minus = 1;
	check_minus_and_format(&str, &minus);
	while (ft_isdigit(*str) && *str)
	{
		if (ft_check_flow(num, *str, minus))
			return (ft_check_flow(num, *str, minus) - 2);
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (*str && *(str++) != '.')
		ft_error("worng input : type should be number");
	result = (double)(num * minus);
	num = 10;
	while (ft_isdigit(*str) && *str)
	{
		result += (*str - '0') / num;
		num *= 10;
		str++;
	}
	if (*str && !ft_isdigit(*str))
		ft_error("worng input : type should be number");
	return (result);
}
