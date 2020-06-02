/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:56:32 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/02 16:11:52 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		release_key(int keycode, t_env *env)
{
	if (keycode == W || keycode == UP)
		env->move_up = 0;
	else if (keycode == S || keycode == DOWN)
		env->move_down = 0;
	else if (keycode == D || keycode == RIGHT)
		env->move_right = 0;
	else if (keycode == A || keycode == LEFT)
		env->move_left = 0;
	else if (keycode == 257 || keycode == 258)	//Shift for running
		env->move_speed = 0.15;
	return (0);
}

int		press_key(int keycode, t_env *env)
{
	if (keycode == W || keycode == UP)
		env->move_up = 1;
	else if (keycode == S || keycode == DOWN)
		env->move_down = 1;
	else if (keycode == D || keycode == RIGHT)
		env->move_right = 1;
	else if (keycode == A || keycode == LEFT)
		env->move_left = 1;
	else if (keycode == 257 || keycode == 258)	//Shift for running
		env->move_speed = 0.3;
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int		event_key(t_env *env)
{
	double	old_dir_x;
	double	old_plane_x;

	if (env->move_up == 1)
    {
        if(env->world_map[(int)(env->pos.x + env->dir.x * env->move_speed)][(int)env->pos.y] == 0)
            env->pos.x += env->dir.x * env->move_speed;
		if(env->world_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * env->move_speed)] == 0)
            env->pos.y += env->dir.y * env->move_speed;
    }
    if (env->move_down == 1)
    {
        if(env->world_map[(int)(env->pos.x - env->dir.x * 0.15)][(int)env->pos.y] == 0)
            env->pos.x -= env->dir.x * 0.15;
		if(env->world_map[(int)env->pos.x][(int)(env->pos.y - env->dir.y * 0.15)] == 0)
            env->pos.y -= env->dir.y * 0.15;
    }
    if (env->move_left == 1)
    {
        //both camera direction and camera plane must be rotated
		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(0.04) - env->dir.y * sin(0.04);
		env->dir.y = old_dir_x * sin(0.04) + env->dir.y * cos(0.04);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(0.04) - env->plane.y * sin(0.04);
		env->plane.y = old_plane_x * sin(0.04) + env->plane.y * cos(0.04);
    }
    if (env->move_right == 1)
    {
        //both camera direction and camera plane must be rotated
		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(-0.04) - env->dir.y * sin(-0.04);
		env->dir.y = old_dir_x * sin(-0.04) + env->dir.y * cos(-0.04);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(-0.04) - env->plane.y * sin(-0.04);
		env->plane.y = old_plane_x * sin(-0.04) + env->plane.y * cos(-0.04);
    }
	draw_again(env);
	return (1);
}
