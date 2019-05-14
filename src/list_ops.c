/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:44:45 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 15:45:55 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			smash_list(t_list **lines, t_map **map)
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

int			count_links(t_list *lines)
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

void		rev_list(t_list **alst)
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
