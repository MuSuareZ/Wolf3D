/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:07:47 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/29 17:28:43 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			init_img(t_env *env)
{
	env->img.image = mlx_new_image(env->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	env->img.ptr = mlx_get_data_addr(env->img.image, &env->img.bpp,
		&env->img.line_s, &env->img.endian);
	env->img.bpp /= 8;
}

void			img_pixel_put(t_env *env, int x, int y, int color)
{
	if (env->texture == 1 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
	{
		env->y_text = abs((((y * 256 - SCREEN_HEIGHT * 128 +
			env->line_height * 128) * 64) / env->line_height) / 256);
		ft_memcpy(env->img.ptr + 4 * SCREEN_WIDTH * y + x * 4,
			&env->tex[env->id].ptr[env->y_text % 64 *
				env->tex[env->id].line_s + env->x_text %
					64 * env->tex[env->id].bpp / 8], sizeof(int));
	}
	else if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
		ft_memcpy(env->img.ptr + 4 * SCREEN_WIDTH * y + x * 4,
				&color, sizeof(int));
}
