/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:24:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 16:26:47 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		i_wish_this_worked(t_map *map)
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
			current->color = jebus(0xFF0000, 0xFFFFFF, why_me_double(current->z,
				map->depth_min, map->depth_max));
			vector.x++;
		}
		vector.y++;
	}
}

void		map_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	vector;
	t_vector	current;

	min = INT32_MIN;
	max = INT32_MAX;
	vector.y = -1;
	while (++vector.y < map->height)
	{
		vector.x = -1;
		while (++vector.x < map->height)
		{
			current = *map->vectors[(int)vector.y * map->width + (int)vector.x];
			if (current.z < min)
				min = current.z;
			if (current.z > max)
				max = current.z;
		}
	}
	map->depth_min = min;
	map->depth_max = max;
}