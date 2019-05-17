/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:24:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/17 02:25:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			map_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	vector;
	t_vector	current;

	min = INT32_MAX;
	max = INT32_MIN;
	vector.y = 0;
	while (vector.y < map->height)
	{
		vector.x = 0;
		while (vector.x < map->width)
		{
			current = *map->vectors[(int)vector.y * map->width + (int)vector.x];
			if (current.z < min)
				min = current.z;
			if (current.z > max)
				max = current.z;
			vector.x++;
		}
		vector.y++;
	}
	map->depth_min = min;
	map->depth_max = max;
}

double			convert_(double z_vector, double min, double max)
{
	if (z_vector == min)
		return (0.0);
	if (z_vector == max)
		return (1.0);
	return ((z_vector - min) / (max - min));
}
