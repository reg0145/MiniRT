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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			c;

	num = (unsigned int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	c = num % 10 + '0';
	num /= 10;
	if (num > 0)
		ft_putnbr_fd(num, fd);
	write(fd, &c, 1);
}
