/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:43:19 by msuarez-          #+#    #+#             */
/*   Updated: 2020/07/01 16:22:47 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		check_hit(t_env *env)
{
	env->hit = 0;
	while (env->hit == 0)
	{
		if (env->side_dist.x < env->side_dist.y)
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
		if (env->world_map.map[env->map.x][env->map.y] > 0)
			env->hit = 1;
	}
}

void		check_step(t_env *env)
{
	if (env->ray_dir.x < 0)
	{
		env->step.x = -1;
		env->side_dist.x = (env->ray_pos.x - env->map.x) * env->delta_dist.x;
	}
	else
	{
		env->step.x = 1;
		env->side_dist.x = (env->map.x + 1.0 - env->ray_pos.x) *
							env->delta_dist.x;
	}
	if (env->ray_dir.y < 0)
	{
		env->step.y = -1;
		env->side_dist.y = (env->ray_pos.y - env->map.y) * env->delta_dist.y;
	}
	else
	{
		env->step.y = 1;
		env->side_dist.y = (env->map.y + 1.0 - env->ray_pos.y) *
							env->delta_dist.y;
	}
}
