/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 22:35:49 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 16:56:28 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_error(int err_num)
{
	IF_THEN(err_num == 1, ft_printf("usage: ./fdf [file ...]\n"));
	IF_THEN(err_num == 2, ft_printf("error: bad file, yo\n"));
	IF_THEN(err_num == 3, ft_printf("error: you done broke mlx\n"));
	return (1);
}
