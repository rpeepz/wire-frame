/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:28:43 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/16 18:59:44 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int ac, char **av)
{
	t_mlx	*mlx;
	t_map	*map;
	int		fd;

	if (ac < 2)
		return (ft_error(1));
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !parse_fdf(fd, &map))
		return (ft_error(2));
	if (!(mlx = init("baguette")))
		return (ft_error(3));
	mlx->map = map;
	render(mlx);
	return (0);
}

int		ft_error(int err_num)
{
	IF_THEN(err_num == 1, ft_printf("usage: ./fdf [file ...]\n"));
	IF_THEN(err_num == 2, ft_printf("error: bad file, yo\n"));
	IF_THEN(err_num == 3, ft_printf("error: you done broke mlx\n"));
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
