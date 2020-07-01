/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:56:32 by msuarez-          #+#    #+#             */
/*   Updated: 2020/07/01 16:26:47 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				release_key(int keycode, t_env *env)
{
	if (keycode == W || keycode == UP)
		env->player.move_up = 0;
	else if (keycode == S || keycode == DOWN)
		env->player.move_down = 0;
	else if (keycode == D || keycode == RIGHT)
		env->player.move_right = 0;
	else if (keycode == A || keycode == LEFT)
		env->player.move_left = 0;
	else if (keycode == LSHIFT || keycode == RSHIFT)
		env->player.move_speed = 0.15;
	return (0);
}

int				press_key(int keycode, t_env *env)
{
	if (keycode == W || keycode == UP)
		env->player.move_up = 1;
	else if (keycode == S || keycode == DOWN)
		env->player.move_down = 1;
	else if (keycode == D || keycode == RIGHT)
		env->player.move_right = 1;
	else if (keycode == A || keycode == LEFT)
		env->player.move_left = 1;
	else if (keycode == LSHIFT || keycode == RSHIFT)
		env->player.move_speed = 0.3;
	else if (keycode == NUM1)
		env->texture = 1 - env->texture;
	else if (keycode == ESC)
		exit(0);
	return (0);
}

static void		side_key(t_env *env)
{
	if (env->player.move_left == 1)
	{
		env->old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(0.04) - env->dir.y * sin(0.04);
		env->dir.y = env->old_dir_x * sin(0.04) + env->dir.y * cos(0.04);
		env->old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(0.04) - env->plane.y * sin(0.04);
		env->plane.y = env->old_plane_x * sin(0.04) + env->plane.y * cos(0.04);
	}
	if (env->player.move_right == 1)
	{
		env->old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(-0.04) - env->dir.y * sin(-0.04);
		env->dir.y = env->old_dir_x * sin(-0.04) + env->dir.y * cos(-0.04);
		env->old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(-0.04) - env->plane.y * sin(-0.04);
		env->plane.y = env->old_plane_x * sin(-0.04) +
					env->plane.y * cos(-0.04);
	}
}

int				event_key(t_env *env)
{
	if (env->player.move_up == 1)
	{
		if (env->world_map.map[(int)(env->player.pos.x + env->dir.x *
		env->player.move_speed)][(int)env->player.pos.y] == 0)
			env->player.pos.x += env->dir.x * env->player.move_speed;
		if (env->world_map.map[(int)env->player.pos.x][(int)(env->player.pos.y +
		env->dir.y * env->player.move_speed)] == 0)
			env->player.pos.y += env->dir.y * env->player.move_speed;
	}
	if (env->player.move_down == 1)
	{
		if (env->world_map.map[(int)(env->player.pos.x - env->dir.x *
		env->player.move_speed)][(int)env->player.pos.y] == 0)
			env->player.pos.x -= env->dir.x * env->player.move_speed;
		if (env->world_map.map[(int)env->player.pos.x][(int)(env->player.pos.y -
		env->dir.y * env->player.move_speed)] == 0)
			env->player.pos.y -= env->dir.y * env->player.move_speed;
	}
	side_key(env);
	draw_world(env);
	return (1);
}
