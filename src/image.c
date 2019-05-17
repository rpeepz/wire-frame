/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 02:35:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/16 19:00:10 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		construct_color(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

static int		shift_color(int c1, int c2, double p)
{
	int r;
	int g;
	int b;

	if (c1 == c2)
		return (c1);
	r = construct_color((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = construct_color((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = construct_color(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}

void			set_colors(t_map *map)
{
	t_vector	vector;
	t_vector	*current;

	vector.y = 0;
	while (vector.y < map->height)
	{
		vector.x = 0;
		while (vector.x < map->width)
		{
			current = map->vectors[(int)vector.y * map->width + (int)vector.x];
			current->color = shift_color(0x10FF00, 0xFFFFFF,
				convert_(current->z, map->depth_min, map->depth_max));
			vector.x++;
		}
		vector.y++;
	}
}

t_image			*del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(mlx->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image			*new_image(t_mlx *mlx)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)))
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}
