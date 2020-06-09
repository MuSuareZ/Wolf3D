/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:27:30 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/09 17:11:34 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw_points(t_env *env)
{
	if (env->side == 0)
		env->wall_dist = (env->map.x - env->player.pos.x +
		(1 - env->step.x) / 2) / env->ray_dir.x;
	else
		env->wall_dist = (env->map.y - env->player.pos.y +
		(1 - env->step.y) / 2) / env->ray_dir.y;
	env->line_height = (int)(SCREEN_HEIGHT / env->wall_dist);
	env->draw_start = -env->line_height / 2 + SCREEN_HEIGHT / 2;
	if (env->draw_start < 0)
		env->draw_start = 0;
	env->draw_end = env->line_height / 2 + SCREEN_HEIGHT / 2;
	if (env->draw_end >= SCREEN_HEIGHT)
		env->draw_end = SCREEN_HEIGHT - 1;
}

static int		select_color(t_env *env)
{
	if (env->world_map.map[env->map.x][env->map.y] == 1)
		env->color = 0xff0000;
	else if (env->world_map.map[env->map.x][env->map.y] == 2)
		env->color = 0x008000;
	else if (env->world_map.map[env->map.x][env->map.y] == 3)
		env->color = 0x0000ff;
	else if (env->world_map.map[env->map.x][env->map.y] == 4)
		env->color = 0xffffff;
	else
		env->color = 0xff66ff;
	if (env->side == 1 && env->world_map.map[env->map.x][env->map.y] != 1)
		env->color = env->color / 2;
	return (env->color);
}

static void		ver_line(t_env *env, int x, int y0, int y1)
{
	select_color(env);
	while (y0 != y1)
	{
		img_pixel_put(env, x, y0, env->color);
		y0++;
	}
}

void			*draw_world(void *env_ptr)
{
	t_env		*env;
	int			x;
	double		camera_x;

	env = (t_env *)env_ptr;
	x = env->thread_id;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		env->ray_dir.x = env->dir.x + env->plane.x * camera_x;
		env->ray_dir.y = env->dir.y + env->plane.y * camera_x;
		env->map.x = (int)env->player.pos.x;
		env->map.y = (int)env->player.pos.y;
		env->delta_dist.x = sqrt(1 + (env->ray_dir.y * env->ray_dir.y)
			/ (env->ray_dir.x * env->ray_dir.x));
		env->delta_dist.y = sqrt(1 + (env->ray_dir.x * env->ray_dir.x)
			/ (env->ray_dir.y * env->ray_dir.y));
		check_step(env);
		check_hit(env);
		draw_points(env);
		ver_line(env, x, env->draw_start, env->draw_end);
		x += THREADS;
	}
	return (NULL);
}
