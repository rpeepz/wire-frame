/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/14 01:29:29 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1280
# define HEIGHT 720


# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"

int				ft_error(int err_num);

typedef struct 	s_mlx
{
	void		*mlx;
	void		*window;
}				t_mlx;
#endif
