/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:27:30 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/03 14:17:53 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		check_hit(t_env *env)
{
	env->hit = 0;
	while (env->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(env->side_dist.x < env->side_dist.y)
		{
			env->side_dist.x += env->delta_dist.x;
			env->map.x += env->step.x;
			env->side = 0;
		}
		else
		{
			env->side_dist.y += env->delta_dist.y;
			env->map.y += env->step.y;
			env->side = 1;
		}
		//Check if ray has hit a wall
		if(env->world_map[env->map.x][env->map.y] > 0)
			env->hit = 1;
	}
}

static void		check_step(t_env *env)
{
	//calculate step and initial sideDist
	if(env->ray_dir.x < 0)
	{
		env->step.x = -1;
		env->side_dist.x = (env->pos.x - env->map.x) * env->delta_dist.x;
	}
	else
	{
		env->step.x = 1;
		env->side_dist.x = (env->map.x + 1.0 - env->pos.x) * env->delta_dist.x;
	}
	if(env->ray_dir.y < 0)
	{
		env->step.y = -1;
		env->side_dist.y = (env->pos.y - env->map.y) * env->delta_dist.y;
	}
	else
	{
		env->step.y = 1;
		env->side_dist.y = (env->map.y + 1.0 - env->pos.y) * env->delta_dist.y;
	}
}

static int		select_color(t_env *env)
{
	if (env->world_map[env->map.x][env->map.y] == 1)
		env->color = 0xff0000;
	else if (env->world_map[env->map.x][env->map.y] == 2)
		env->color = 0x008000;
	else if (env->world_map[env->map.x][env->map.y] == 3)
		env->color = 0x0000ff;
	else if (env->world_map[env->map.x][env->map.y] == 4)
		env->color = 0xffffff;
	else
		env->color = 0xff66ff;
	if (env->side == 1 && env->world_map[env->map.x][env->map.y] != 1)
		env->color = env->color / 2;
	return (env->color);
}

static void		verLine(t_env *env, int x, int y0, int y1, int color)
{
	while (y0 != y1)
	{
		img_pixel_put(env, x, y0, color);
		y0++;
	}
}

void			*draw_world(void *env_ptr)
{
	t_env		*env;
	int			x;
	int			line_height;
	double		wall_dist;
	double		camera_x;

	env = (t_env *)env_ptr;
	x = env->thread_id;
	while (x < SCREEN_WIDTH)
    {
		//calculate ray position and direction
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;	//x-coordinate in camera space
		env->ray_dir.x = env->dir.x + env->plane.x * camera_x;
		env->ray_dir.y = env->dir.y + env->plane.y * camera_x;
		//which box of the map we're in
		env->map.x = (int)env->pos.x;
		env->map.y = (int)env->pos.y;
		//length of ray from one x or y-side to next x or y-side
		env->delta_dist.x = sqrt(1 + (env->ray_dir.y * env->ray_dir.y)
			/ (env->ray_dir.x * env->ray_dir.x));
		env->delta_dist.y = sqrt(1 + (env->ray_dir.x * env->ray_dir.x)
			/ (env->ray_dir.y * env->ray_dir.y));
		check_step(env);
		//perform DDA
		check_hit(env);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (env->side == 0)
			wall_dist = (env->map.x - env->pos.x + (1 - env->step.x) / 2) / env->ray_dir.x;
		else
			wall_dist = (env->map.y - env->pos.y + (1 - env->step.y) / 2) / env->ray_dir.y;
		//Calculate height of line to draw on screen
		line_height = (int)(SCREEN_HEIGHT / wall_dist);
		//calculate lowest and highest pixel to fill in current stripe
		env->draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if(env->draw_start < 0)
			env->draw_start = 0;
		env->draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (env->draw_end >= SCREEN_HEIGHT)
			env->draw_end = SCREEN_HEIGHT - 1;
		//draw the pixels of the stripe as a vertical line
		verLine(env, x, env->draw_start, env->draw_end, select_color(env));
		x += THREADS;
	}
	return (NULL);
}
