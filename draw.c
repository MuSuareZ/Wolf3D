/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:27:30 by msuarez-          #+#    #+#             */
/*   Updated: 2020/07/01 16:12:56 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw_points(t_env *env)
{
	env->line_height = (int)(SCREEN_HEIGHT / env->wall_dist);
	env->draw_start = -env->line_height / 2 + SCREEN_HEIGHT / 2;
	if (env->draw_start < 0)
		env->draw_start = 0;
	env->draw_end = env->line_height / 2 + SCREEN_HEIGHT / 2;
	if (env->draw_end >= SCREEN_HEIGHT)
		env->draw_end = SCREEN_HEIGHT - 1;
}

void			draw_wall(int x, t_env *env)
{
	if (env->texture == 1)
	{
		env->id = env->world_map.map[env->map.x][env->map.y];
		if (env->side == 0)
			env->wall_dist = env->ray_pos.y + env->wall_dist * env->ray_dir.y;
		else
			env->wall_dist = env->ray_pos.x + env->wall_dist * env->ray_dir.x;
		env->x_text = (int)(env->wall_dist * (double)(64));
		if (env->side == 0 && env->ray_dir.x > 0)
			env->x_text = 64 - env->x_text - 1;
		if (env->side == 1 && env->ray_dir.y < 0)
			env->x_text = 64 - env->x_text - 1;
		env->x_text = abs(env->x_text);
	}
	while (++env->draw_start != env->draw_end)
		img_pixel_put(env, x, env->draw_start, env->color);
}

void			draw_sky(t_env *env)
{
	env->x_text = 0;
	while (env->x_text < SCREEN_WIDTH)
	{
		env->y_text = 0;
		while (env->y_text < SCREEN_HEIGHT / 2)
		{
			ft_memcpy(env->img.ptr + 4 * SCREEN_WIDTH * env->y_text +
				env->x_text * 4, &env->tex[6].ptr[env->y_text % 512 *
					env->tex[6].line_s + env->x_text % 512 *
						env->tex[6].bpp / 8], sizeof(int));
			env->y_text++;
		}
		env->x_text++;
	}
}

void			draw_floor(t_env *env, int x)
{
	int		y;

	if (env->draw_end > 0)
	{
		env->color = 0x333333;
		y = env->draw_end - 1;
		if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
			while (++y < SCREEN_HEIGHT)
				ft_memcpy(env->img.ptr + 4 * SCREEN_WIDTH * y + x * 4,
						&env->color, sizeof(int));
	}
}

void			draw_world(t_env *env)
{
	init_img(env);
	if (env->texture == 1)
		draw_sky(env);
	env->x = 0;
	while (env->x++ < SCREEN_WIDTH)
	{
		raycast_init(env, env->x);
		draw_points(env);
		if (env->side == 1)
			env->color = 0x008000;
		else
			env->color = 0x00FF00;
		draw_wall(env->x, env);
		draw_floor(env, env->x);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.image, 0, 0);
	mlx_destroy_image(env->mlx, env->img.image);
}
