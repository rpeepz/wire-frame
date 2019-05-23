/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/22 18:04:26 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1600
# define HEIGHT 900
# define K_1 18
# define K_R 15
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_SPC 49
# define K_ESC 53
# define K_LEFTARR 123
# define K_RIGHTARR 124
# define K_UPARR 126
# define K_DOWNARR 125

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>

/*
**	STRUCTS
*/

typedef struct	s_mouse
{
	char		isdown;
	char		kydown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}				t_mouse;
typedef struct	s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
}				t_cam;

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
typedef struct	s_line
{
	t_vector	start;
	t_vector	stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}				t_line;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	int			map_tot;
	int			map_cur;
	t_image		*image;
	t_map		**map;
	t_mouse		*mouse;
	t_cam		*cam;
}				t_mlx;

/*
**	LIST OPS
*/

int				smash_list(t_list **lines, t_map **map);
int				count_links(t_list *lines);
int				gross(char ***split_map_coordinates);
void			rev_list(t_list **alst);
void			set_colors(t_map *map);
void			render(t_mlx *mlx);
void			line(t_mlx *mlx, t_vector p1, t_vector p2);

/*
**	STRUCT RETURNS
*/

t_mlx			*init(char *title, int total);
t_mlx			*mlxdel(t_mlx *mlx);
t_image			*new_image(t_mlx *mlx);
t_image			*del_image(t_mlx *mlx, t_image *img);
t_vector		project_vector(t_vector v, t_mlx *mlx);

/*
**	INPUTS
*/

int				hook_mouseup(int button, int x, int y, t_mlx *mlx);
int				hook_mousedown(int button, int x, int y, t_mlx *mlx);
int				hook_mousemove(int x, int y, t_mlx *mlx);
int				hook_keydown(int key, t_mlx *mlx);

double			convert_(double z_vector, double min, double max);
int				shift_color(int c1, int c2, double p);
void			map_depth(t_map *map);
int				ft_error(int err_num);
int				parse_fdf(int fd, t_map **map);

#endif

/*
**	FUNCTIONS FROM MINILIBX
**
**
**
**
**
**
**
**	Many thanks to pbondoer for helping me understand the use of
**	mlx library and use of integrated structures for this project
**	https://github.com/pbondoer/42-FdF
**	Full credit goes to him!
*/
