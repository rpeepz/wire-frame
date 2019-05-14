/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 02:35:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 16:25:02 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	why_me_double(double val, double first, double second)
{
	if (val == first)
		return (0.0);
	if (val == second)
		return (1.0);
	return ((val - first) / (second - first));
}

int			why_me(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int			jebus(int c1, int c2, double p)
{
	int r;
	int g;
	int b;

	if (c1 == c2)
		return (c1);
	r = why_me((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = why_me((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = why_me(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}

t_image		*del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(mlx->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image		*new_image(t_mlx *mlx)
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