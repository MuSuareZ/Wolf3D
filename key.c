/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:56:32 by msuarez-          #+#    #+#             */
/*   Updated: 2020/03/20 18:26:00 by msuarez-         ###   ########.fr       */
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

int		event_key(int keycode, t_env *env)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == W)
    {
        if(env->world_map[(int)(env->pos.x + env->dir.x * 0.5)][(int)env->pos.y] == 0)
            env->pos.x += env->dir.x * 0.5;
		if(env->world_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.5)] == 0)
            env->pos.y += env->dir.y * 0.5;
    }
    if (keycode == S)
    {
        if(env->world_map[(int)(env->pos.x - env->dir.x * 0.5)][(int)env->pos.y] == 0)
            env->pos.x -= env->dir.x * 0.5;
		if(env->world_map[(int)env->pos.x][(int)(env->pos.y - env->dir.y * 0.5)] == 0)
            env->pos.y -= env->dir.y * 0.5;
    }
    if (keycode == A)
    {
        //both camera direction and camera plane must be rotated
		double oldDirX = env->dir.x;
		env->dir.x = env->dir.x * cos(0.08) - env->dir.y * sin(0.08);
		env->dir.y = oldDirX * sin(0.08) + env->dir.y * cos(0.08);
		double oldPlaneX = env->plane.x;
		env->plane.x = env->plane.x * cos(0.08) - env->plane.y * sin(0.08);
		env->plane.y = oldPlaneX * sin(0.08) + env->plane.y * cos(0.08);
    }
    if (keycode == D)
    {
        //both camera direction and camera plane must be rotated
		double oldDirX = env->dir.x;
		env->dir.x = env->dir.x * cos(-0.08) - env->dir.y * sin(-0.08);
		env->dir.y = oldDirX * sin(-0.08) + env->dir.y * cos(-0.08);
		double oldPlaneX = env->plane.x;
		env->plane.x = env->plane.x * cos(-0.08) - env->plane.y * sin(-0.08);
		env->plane.y = oldPlaneX * sin(-0.08) + env->plane.y * cos(-0.08);
    }
	draw_again(env);
	return (1);
}
