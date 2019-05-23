/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:28:43 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/22 17:58:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int ac, char **av)
{
	t_mlx	*mlx;
	t_map	**map;
	int		fd[ac];
	int		i;

	if ((i = -1) && ac < 2)
		return (ft_error(1));
	fd[ac - 1] = 0;
	if (!(map = (t_map **)malloc(sizeof(*map) * ac)))
		return (ft_error(4));
	map[ac - 1] = NULL;
	while (++i < ac - 1)
		fd[i] = open(av[i + 1], O_RDONLY);
	i = -1;
	while (++i < ac - 1)
		if (fd[i] < 0 || !parse_fdf(fd[i], &map[i]))
			return (ft_error(2));
	if (!(mlx = init("baguette", ac - 2)))
		return (ft_error(3));
	mlx->map = map;
	render(mlx);
	mlx_key_hook(mlx->window, hook_keydown, mlx);
	mlx_hook(mlx->window, 4, 0, hook_mousedown, mlx);
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
	mlx_hook(mlx->window, 5, 0, hook_mouseup, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

int		ft_error(int err_num)
{
	IF_THEN(err_num == 1, ft_printf("usage: ./fdf [file ...]\n"));
	IF_THEN(err_num == 2, ft_printf("error: FATAL ERROR\n"));
	IF_THEN(err_num == 3, ft_printf("error: you done broke mlx\n"));
	IF_RETURN(err_num == 4, ft_printf("error: malloc returned %s\n", NULL));
	return (1);
}

int		gross(char ***plz_no)
{
	char	**yeet;
	int		dora;

	dora = 0;
	yeet = *plz_no;
	while (*yeet)
	{
		ft_strdel(yeet);
		dora++;
		yeet = &(*plz_no)[dora];
	}
	ft_memdel((void **)plz_no);
	return (0);
}
