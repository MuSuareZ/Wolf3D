/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:56:32 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/01 15:40:40 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			mouse_move(int x, int y, t_env *e)
{
	if ((x >= 0 && x <= screenWidth) && (y >= 0 && y <= screenHeight))
	{
		e->pos.x = x;
		e->pos.y = y;
	}
	draw_again(e);
	return (1);
}

int		release_key(int keycode, t_env *env)
{
	if (keycode == W)
		env->move_up = 0;
	else if (keycode == S)
		env->move_down = 0;
	else if (keycode == D)
		env->move_right = 0;
	else if (keycode == A)
		env->move_left = 0;
	else if (keycode == 257 || keycode == 258)	//Shift for running
		env->move_speed = 0.15;
	return (0);
}

int		press_key(int keycode, t_env *env)
{
	if (keycode == W)
		env->move_up = 1;
	else if (keycode == S)
		env->move_down = 1;
	else if (keycode == D)
		env->move_right = 1;
	else if (keycode == A)
		env->move_left = 1;
	else if (keycode == 257 || keycode == 258)	//Shift for running
		env->move_speed = 0.3;
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int		event_key(t_env *env)
{
	double	oldDirX;
	double	oldPlaneX;

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
		oldDirX = env->dir.x;
		env->dir.x = env->dir.x * cos(0.04) - env->dir.y * sin(0.04);
		env->dir.y = oldDirX * sin(0.04) + env->dir.y * cos(0.04);
		oldPlaneX = env->plane.x;
		env->plane.x = env->plane.x * cos(0.04) - env->plane.y * sin(0.04);
		env->plane.y = oldPlaneX * sin(0.04) + env->plane.y * cos(0.04);
    }
    if (env->move_right == 1)
    {
        //both camera direction and camera plane must be rotated
		oldDirX = env->dir.x;
		env->dir.x = env->dir.x * cos(-0.04) - env->dir.y * sin(-0.04);
		env->dir.y = oldDirX * sin(-0.04) + env->dir.y * cos(-0.04);
		oldPlaneX = env->plane.x;
		env->plane.x = env->plane.x * cos(-0.04) - env->plane.y * sin(-0.04);
		env->plane.y = oldPlaneX * sin(-0.04) + env->plane.y * cos(-0.04);
    }
	draw_again(env);
	return (1);
}
