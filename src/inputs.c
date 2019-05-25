/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:20:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/22 22:37:46 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	mlx->mouse->isdown |= 1 << button;
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	mlx->mouse->isdown &= ~(1 << button);
	return (0);
}

static t_vector	vector_at(t_map *map, int x, int y)	//REMOVE
{													//REMOVE
	return (*map->vectors[y * map->width + x]);		//REMOVE
}													//REMOVE
													//REMOVE
static t_vector	rotatez(t_vector p, t_cam *r)		//REMOVE
{													//REMOVE
	t_vector	v;									//REMOVE
													//REMOVE
	v.x = cos(r->y) * p.x + sin(r->y) * p.y;		//REMOVE
	v.y = -sin(r->y) * p.x + cos(r->y) * p.y;		//REMOVE
	p.y = v.y;										//REMOVE
	v.z = cos(r->x) * p.z - sin(r->x) * -p.y;		//REMOVE
	v.y = sin(r->x) * p.z + cos(r->x) * -p.y;		//REMOVE
	v.color = p.color;								//REMOVE
	return (v);										//REMOVE
}													//REMOVE
													//REMOVE
static t_vector		project_vectorz(t_vector v, t_mlx *mlx)	//REMOVE
{															//REMOVE
	t_map *map;												//REMOVE
															//REMOVE
	map = *(mlx->map);										//REMOVE
	v.x -= (double)(map->width - 1) / 2.0f;					//REMOVE
	v.y -= (double)(map->height - 1) / 2.0f;				//REMOVE
	v = rotatez(v, mlx->cam);								//REMOVE
	v.x *= mlx->cam->scale;									//REMOVE
	v.y *= mlx->cam->scale;									//REMOVE
	v.x += mlx->cam->offsetx;								//REMOVE
	v.y += mlx->cam->offsety;								//REMOVE
	return (v);												//REMOVE
}															//REMOVE

int		hook_mousemove(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isdown & (1 << 1) && mlx->mouse->isdown & (1 << 2))
	{
		mlx->cam->offsetx += (x - mlx->mouse->lastx);
		mlx->cam->offsety += (y - mlx->mouse->lasty);
	}
	else if (mlx->mouse->isdown & (1 << 1))
	{
		mlx->cam->x += (mlx->mouse->lasty - y) / 350.0f;
		mlx->cam->y -= (mlx->mouse->lastx - x) / 400.0f;
	}
	else if (mlx->mouse->isdown & (1 << 2))
	{
		mlx->cam->scale += (mlx->mouse->lasty - y) / 10.0f + 0.5f;
		if (mlx->cam->scale < 1)
			mlx->cam->scale = 1;
	}
	if (mlx->mouse->kydown == K_R)			//REMOVE
	{	for(int i = 0; i < 20; i++)			//REMOVE
		{										//REMOVE
			mlx->cam->y -= (double)i / 800.0f;	//REMOVE
												//REMOVE
			int			x1 = -1;					//REMOVE
			int			y1;							//REMOVE
			t_vector	v;							//REMOVE
			t_map		*map = *(mlx->map);				//REMOVE
			while (++x1 < map->width)					//REMOVE
			{												//REMOVE
				y1 = -1;									//REMOVE
				while (++y1 < map->height)						//REMOVE
				{													//REMOVE
					v = project_vectorz(vector_at(map, x1, y1), mlx);	//REMOVE
					if (x1 + 1 < map->width)								//REMOVE
						line(mlx, v,											//REMOVE
							project_vectorz(vector_at(map, x1 + 1, y1), mlx));	//REMOVE
					if (y1 + 1 < map->height)										//REMOVE
						line(mlx, v,												//REMOVE
							project_vectorz(vector_at(map, x1, y1 + 1), mlx));		//REMOVE
				}																	//REMOVE
			}																		//REMOVE
			mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);	//REMOVE
		}																				//REMOVE
		mlx->mouse->kydown = 0;														//REMOVE
		//render(mlx);															//REMOVE
		return (0);															//REMOVE
	}
	if (mlx->mouse->isdown) //SUBSTITUE THE FOLLOWING WITH // render(mlx);
		render(mlx);
	else
	{	//CLEAR SCREEN WHEN MOUSE IS STILL
		return 0;
		if (mlx->mouse->lastx == mlx->mouse->x && mlx->mouse->lasty == mlx->mouse->y)
			ft_bzero(mlx->image->ptr, WIDTH * HEIGHT * mlx->image->bpp);
//		else if (!mlx->mouse->isdown)
//			ft_bzero(mlx->image->ptr, WIDTH * HEIGHT * mlx->image->bpp);
		int			x1 = -1;
		int			y1;
		t_vector	v;
		t_map		*map = *(mlx->map);
		while (++x1 < map->width)
		{
			y1 = -1;
			while (++y1 < map->height)
			{
				v = project_vectorz(vector_at(map, x1, y1), mlx);
				if (x1 + 1 < map->width)
					line(mlx, v,
						project_vectorz(vector_at(map, x1 + 1, y1), mlx));
				if (y1 + 1 < map->height)
					line(mlx, v,
						project_vectorz(vector_at(map, x1, y1 + 1), mlx));
			}
		}
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	}
	return (0);
}

/*
**	TODO
**	will attempt to create a loop to programatically raise an entire
**	row or collumn
*/

int		hook_keydown(int key, t_mlx *mlx)
{
	t_map		*map;
	t_vector	*v;
	t_vector	**vectors;
	int			i;

	(void)mlx;
	ft_printf("key: %d\n", key);
//	quit program
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
//	set keydown and return
	IF_RETURN(key == K_1 && (mlx->mouse->kydown = K_1), 0);
	IF_RETURN(key == K_R && (mlx->mouse->kydown = K_R), 0);
//	raising by 1 on z-axis a single point
	if (key == K_SPC)
	{
		map = *(mlx->map);
		v = *map->vectors;
		v->z++;
		map_depth(map);
		set_colors(map);
		render(mlx);
	}
//	raising by 1 on z-axis a row along the height
	else if (key == K_W || key == K_S)
	{
		map = *(mlx->map);
		vectors = map->vectors;
		if (mlx->mouse->kydown == K_1)
		{
			vectors += 1; // TODO
			mlx->mouse->kydown = 0;
		}
		if (key == K_W)
			while (*vectors)
			{
				(*vectors)->z += 1;
				vectors += map->width;
			}
		else if (key == K_S)
			while (*vectors)
			{
				(*vectors)->z -= 1;
				vectors += map->width;
			}
		
		map_depth(map); //sets depth for color calculations
		set_colors(map);//sets color gradient based on depth
		render(mlx);
	}
//	raising by 1 on z-axis a row along the width
	else if (key == K_A || key == K_D)
	{
		map = *(mlx->map);
		vectors = map->vectors;
		i = 0;
		if (mlx->mouse->kydown == K_1)
		{
			*vectors += 1;
			mlx->mouse->kydown = 0;
		}
		if (key == K_D)
			while (i++ < map->width)
			{
				(*vectors)->z += 1;
				vectors++;
			}
		else if (key == K_A)
			while (i++ < map->width)
			{
				(*vectors)->z -= 1;
				vectors++;
			}
		map_depth(map); //sets depth for color calculations
		set_colors(map);//sets color gradient based on depth
		render(mlx);
	}
//	swap or snap between given maps
	else if (key == K_LEFTARR || key == K_RIGHTARR || key == K_UPARR || key == K_DOWNARR)
	{
		if (key == K_RIGHTARR || key == K_UPARR)
		{
			while (mlx->map_cur < mlx->map_tot)
			{
				mlx->map_cur++;
				mlx->map++;
				if (key == K_RIGHTARR)
					break ;
			}
		}
		else if (key == K_LEFTARR || key == K_DOWNARR)
		{
			while (mlx->map_cur > 0)
			{
				mlx->map_cur--;
				mlx->map--;
				if (key == K_LEFTARR)
					break ;
			}
		}
		render(mlx);
	}
	return (0);
}
