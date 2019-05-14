/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 02:43:38 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 16:47:05 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		store_lines(int fd, t_list **lines)
{
	t_list	*temp;
	char	*line;
	int		ret;
	int		random;

	random = -1;
	while ((ret = get_next_line(fd, &line)))
	{
		if (random == -1)
			random = ft_countwords(line, ' ');
		temp = ft_lstnew(line, ft_strlen(line) + 1);
		if (!temp)
			return (smash_list(lines, NULL));
		ft_lstadd(lines, temp);
		if (random != ft_countwords(line, ' '))
			return (smash_list(lines, NULL));
		ft_strdel(&line);
	}
	if (random == -1 || ret == -1)
		return (smash_list(lines, NULL));
	rev_list(lines);
	return (1);
}

static t_map	*store_map(int width, int height)
{
	t_map	*map;

	if (!(map = ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->width = width;
	map->height = height;
	map->depth_min = 0;
	map->depth_max = 0;
	if (!(map->vectors = ft_memalloc(sizeof(t_vector *) * width * height)))
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}

t_vector	*make_vector(int x, int y, char *str)
{
	t_vector	*vector;

	if (!(vector = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	vector->x = (double)x;
	vector->y = (double)y;
	vector->z = (double)ft_atoi(str);
	vector->color = 0xFFFFFF;
	return (vector);
}

static int		make_more_map(t_map **map, t_list *lines)
{
	t_list	*tmp;
	char	**splt;
	int		x;
	int		y;

	tmp = lines;
	y = -1;
	while (++y < (*map)->height)
	{
		x = -1;
		if (!(splt = ft_strsplit(tmp->content, ' ')))
			return (smash_list(&lines, map));
		while (++x < (*map)->width)
			(*map)->vectors[y * (*map)->width + x] = make_vector(x, y, splt[x]);
		gross(&splt);
		tmp = tmp->next;
	}
	map_depth(*map);
	i_wish_this_worked(*map);
	smash_list(&lines, NULL);
	return (1);
}

int				parse_fdf(int fd, t_map **map)
{
	t_list	*lines;

	lines = NULL;
	if (!(store_lines(fd, &lines)))
		return (0);
	*map = store_map(ft_countwords(lines->content, ' '), count_links(lines));
	if (!*map)
		return (smash_list(&lines, map));
	return (make_more_map(map, lines));
}