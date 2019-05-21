/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:20:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/21 14:05:36 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	mlx->mouse->isdown |= 1 << button;
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	mlx->mouse->isdown &= ~(1 << button);
	return (0);
}

int		hook_mousemove(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isdown & (1 << 1) && mlx->mouse->isdown & (1 << 2))
	{
		mlx->cam->offsetx += (x - mlx->mouse->lastx);
		mlx->cam->offsety += (y - mlx->mouse->lasty);
	}
	else if (mlx->mouse->isdown & (1 << 1))
	{
		mlx->cam->x += (mlx->mouse->lasty - y) / 200.0f;
		mlx->cam->y -= (mlx->mouse->lastx - x) / 200.0f;
	}
	else if (mlx->mouse->isdown & (1 << 2))
	{
		mlx->cam->scale += (mlx->mouse->lasty - y) / 10.0f + 0.5f;
		if (mlx->cam->scale < 1)
			mlx->cam->scale = 1;
	}
	if (mlx->mouse->isdown)
		render(mlx);
	return (0);
}

/*
**	TODO
**	will attempt to create a loop to programatically raise an entire
**	row or collumn
*/

int		hook_keydown(int key, t_mlx *mlx)
{
	t_map		*map;
	t_vector	*v;
	t_vector	**vectors;
	int			i;

	(void)mlx;
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	else
	{
		ft_printf("key: %d\n", key);
	}
//	below holds logic for raising by 1 on z-axis a single point
	if (key == K_SPC)
	{
		map = *(mlx->map);
		v = *map->vectors;
		v->z++;
		render(mlx);
		return (0);
	}
//	below holds logic for raising by 1 on z-axis a row along the height
	if (key == K_W || key == K_S)
	{
		map = *(mlx->map);
		vectors = map->vectors;
		if (key == K_W)
			while (*vectors)
			{
				(*vectors)->z++;
				vectors += map->width;
			}
		else if (key == K_S)
			while (*vectors)
			{
				(*vectors)->z--;
				vectors += map->width;
			}
		render(mlx);
		return (0);
	}
//	below holds logic for raising by 1 on z-axis a row along the width
	if (key == K_A || key == K_D)
	{
		map = *(mlx->map);
		vectors = map->vectors;
		i = 0;
		if (key == K_D)
			while (i++ < map->width)
			{
				(*vectors)->z++;
				vectors++;
			}
		else if (key == K_A)
			while (i++ < map->width)
			{
				(*vectors)->z--;
				vectors++;
			}
		render(mlx);
		return (0);
	}
	else
	{
		if (key == K_RIGHTARR)
			mlx->map++;
		else if (key == K_LEFTARR)
			mlx->map--;
		render(mlx);
	}
	return (0);
}
