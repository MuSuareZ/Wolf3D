/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:07:47 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/04 12:00:53 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		idx(int row, int col, int dim)
{
	return (row * dim + col);
}

void			init_img(t_env *env)
{
	t_image	*img;

	img = &env->img;
	img->image = mlx_new_image(env->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->line_s,
								&img->endian);
	img->bpp /= 8;
}

void			img_pixel_put(t_env *env, double x, double y, int color)
{
	t_image *img;

	img = &(env->img);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(int *)(img->ptr + (int)(idx(y, x, SCREEN_WIDTH) * img->bpp)) = color;
}

void			clear_img(t_env *env)
{
	t_image *img;

	img = &(env->img);
	ft_bzero(img->ptr, (SCREEN_WIDTH * SCREEN_HEIGHT) * img->bpp);
}
