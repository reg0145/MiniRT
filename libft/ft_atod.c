/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:43:14 by nheo              #+#    #+#             */
/*   Updated: 2022/11/22 19:17:37 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static void	check_minus_and_format(char **str, int *minus)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*minus *= (-1);
		(*str)++;
	}
	if (!ft_isdigit(**str))
		ft_error("worng input : atod() not a number");
}

static double	add_decimal(char *str, double num)
{
	double	tmp;

	tmp = 10;
	while (*str && ft_isdigit(*str))
	{
		num += (*str - '0') / tmp;
		tmp *= 10;
		str++;
	}
	if (*str && !ft_isdigit(*str))
		ft_error("worng input : atod() not a number");
	return (num);
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
		if (num == -INFINITY || num == INFINITY)
			ft_error("double : out of range");
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (*str && *(str++) != '.')
		ft_error("worng input : atod() not a number");
	result = (double)(num * minus);
	result = add_decimal(str, result);
	return (result);
}