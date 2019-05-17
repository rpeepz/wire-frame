/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 19:51:31 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/17 03:36:34 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
**	image_set_pixel(mlx->image, (int)p1->x, (int)p1->y,
**			shift_color(p1->color, p2->color, percent));
*/

static int		line_process_point(t_mlx *mlx, t_line *l, t_vector *p1,
		t_vector *p2)
{
	double	percent;

	if (p1->x < 0 || p1->x >= WIDTH || p1->y < 0 || p1->y >= HEIGHT
		|| p2->x < 0 || p2->x >= WIDTH || p2->y < 0 || p2->y >= HEIGHT)
		return (1);
	percent = (l->dx > l->dy ?
			convert_((int)p1->x, (int)l->start.x, (int)l->stop.x)
			: convert_((int)p1->y, (int)l->start.y, (int)l->stop.y));
	if ((int)p1->x < 0 || (int)p1->x >= WIDTH ||
		(int)p1->y < 0 || (int)p1->y >= HEIGHT)
		;
	else
		*(int *)(mlx->image->ptr +
			(((int)p1->x + (int)p1->y * WIDTH) * mlx->image->bpp)) =
				shift_color(p1->color, p2->color, percent)
		;
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

static void		clip_xy(t_vector *v, t_vector *p1, t_vector *p2, int rout)
{
	if (rout & 1)
	{
		v->x = p1->x + (p2->x - p1->x) * (HEIGHT - p1->y) / (p2->y - p1->y);
		v->y = HEIGHT - 1;
	}
	else if (rout & 2)
	{
		v->x = p1->x + (p2->x - p1->x) * -p1->y / (p2->y - p1->y);
		v->y = 0;
	}
	else if (rout & 4)
	{
		v->x = WIDTH - 1;
		v->y = p1->y + (p2->y - p1->y) * (WIDTH - p1->x) / (p2->x - p1->x);
	}
	else
	{
		v->x = 0;
		v->y = p1->y + (p2->y - p1->y) * -p1->x / (p2->x - p1->x);
	}
}

static int		region(int x, int y)
{
	int c;

	c = 0;
	if (y >= HEIGHT)
		c |= 1;
	else if (y < 0)
		c |= 2;
	if (x >= WIDTH)
		c |= 4;
	else if (x < 0)
		c |= 8;
	return (c);
}

static int		lineclip(t_vector *p1, t_vector *p2)
{
	t_vector	v;
	int			r1;
	int			r2;
	int			rout;

	r1 = region(p1->x, p1->y);
	r2 = region(p2->x, p2->y);
	while (!(!(r1 | r2) || (r1 & r2)))
	{
		rout = r1 ? r1 : r2;
		clip_xy(&v, p1, p2, rout);
		if (rout == r1)
		{
			p1->x = v.x;
			p1->y = v.y;
			r1 = region(p1->x, p1->y);
		}
		else
		{
			p2->x = v.x;
			p2->y = v.y;
			r2 = region(p2->x, p2->y);
		}
	}
	return (!(r1 | r2));
}

void			line(t_mlx *mlx, t_vector p1, t_vector p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.stop = p2;
	if (!lineclip(&p1, &p2))
		return ;
	line.dx = (int)abs((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)abs((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (line_process_point(mlx, &line, &p1, &p2))
			break ;
}
