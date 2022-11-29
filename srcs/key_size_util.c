/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_size_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:50 by donghyuk          #+#    #+#             */
/*   Updated: 2022/11/28 16:36:42 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "minirt.h"

int	is_size_key(int keycode)
{
	if (keycode == KEY_SIZE_UP || keycode == KEY_SIZE_DOWN)
		return (TRUE);
	return (FALSE);
}
