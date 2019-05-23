/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:44:45 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/22 18:44:55 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				smash_list(t_list **lines, t_map **map)
{
	t_list	*next;

	while (*lines)
	{
		next = (*lines)->next;
		ft_memdel(&(*lines)->content);
		ft_memdel((void **)lines);
		*lines = next;
	}
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	return (0);
}

int				count_links(t_list *lines)
{
	int		i;

	i = 0;
	while (lines != NULL)
	{
		lines = lines->next;
		i++;
	}
	return (i);
}

void			rev_list(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

static t_vector	rotate(t_vector p, t_cam *r)
{
	t_vector	v;

	v.x = cos(r->y) * p.x + sin(r->y) * p.z;
	v.z = -sin(r->y) * p.x + cos(r->y) * p.z;
	p.z = v.z;
	v.y = cos(r->x) * p.y - sin(r->x) * p.z;
	v.z = sin(r->x) * p.y + cos(r->x) * p.z;
	v.color = p.color;
	return (v);
}

t_vector		project_vector(t_vector v, t_mlx *mlx)
{
	t_map *map;

	map = *(mlx->map);
	v.x -= (double)(map->width - 1) / 2.0f;
	v.y -= (double)(map->height - 1) / 2.0f;
	v = rotate(v, mlx->cam);
	v.x *= mlx->cam->scale;
	v.y *= mlx->cam->scale;
	v.x += mlx->cam->offsetx;
	v.y += mlx->cam->offsety;
	return (v);
}
