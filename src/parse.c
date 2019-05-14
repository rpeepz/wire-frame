/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 02:43:38 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 15:23:35 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		smash_list(t_list **lines, t_map **map)
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

static int		count_links(t_list *lines)
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

static void		rev_list(t_list **alst)
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

int				parse_fdf(int fd, t_map **map)
{
	t_list	*lines;

	lines = NULL;
	if (!(store_lines(fd, &lines)))
		return (0);
	*map = store_map(ft_countwords(lines->content, ' '), count_links(lines));
	if (!*map)
		return (smash_list(&lines, map));
	return (0);
}