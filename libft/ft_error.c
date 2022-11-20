/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:27:37 by nheo              #+#    #+#             */
/*   Updated: 2022/11/20 16:57:19 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "colors.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(YELLOW, 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}