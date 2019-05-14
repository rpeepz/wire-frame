/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 15:33:07 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1280
# define HEIGHT 720


# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"

typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}				t_image;
typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_vector;
typedef struct	s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
}				t_map;
typedef struct	s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
	double		**matrix;
}				t_cam;
typedef struct	s_mouse
{
	char		isdown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}				t_mouse;
typedef struct 	s_mlx
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_cam		*cam;
	t_mouse		*mouse;
}				t_mlx;

int				ft_error(int err_num);
t_mlx			*init(char *title);
t_mlx			*mlxdel(t_mlx *mlx);
t_image			*new_image(t_mlx *mlx);
t_image			*del_image(t_mlx *mlx, t_image *img);
t_map			*store_map(int width, int height);
int				parse_fdf(int fd, t_map **map);
#endif

/*
**	Many thanks to pbondoer for helping me understand the use of
**	mlx library and use of integrated structures for this project
**	https://github.com/pbondoer/42-FdF
**	Full credit goes to him!
*/