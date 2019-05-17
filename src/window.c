/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 22:25:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/17 11:37:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_mlx			*mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	if (mlx->mouse != NULL)
		ft_memdel((void **)&mlx->mouse);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

/*
**		Goes right before mlx->image
**		!(mlx->mouse = ft_memalloc(sizeof(t_mouse))) ||
*/

t_mlx			*init(char *title)
{
	t_mlx	*mlx;

	if (!(mlx = ft_memalloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->mlx = mlx_init()) ||
		!(mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, title)) ||
		!(mlx->cam = ft_memalloc(sizeof(t_cam))) ||
		!(mlx->mouse = ft_memalloc(sizeof(t_mouse))) ||
		!(mlx->image = new_image(mlx)))
		return (mlxdel(mlx));
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIDTH / 2;
	mlx->cam->offsety = HEIGHT / 2;
	return (mlx);
}

static t_vector		vector_at(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
}

void			render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;

	map = mlx->map;
	ft_bzero(mlx->image->ptr, WIDTH * HEIGHT * mlx->image->bpp);
	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			v = project_vector(vector_at(map, x, y), mlx);
			if (x + 1 < map->width)
				line(mlx, v,
					project_vector(*map->vectors[y * map->width + x + 1], mlx));
			if (y + 1 < map->height)
				line(mlx, v,
					project_vector(*map->vectors[y + 1 * map->width + x], mlx));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}
