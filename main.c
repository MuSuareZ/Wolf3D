/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:56:05 by msuarez-          #+#    #+#             */
/*   Updated: 2020/07/01 16:23:11 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_env(t_env *env)
{
	if ((env->mlx = mlx_init()) == (void *)0)
		return ;
	env->win = mlx_new_window(env->mlx, SCREEN_WIDTH,
				SCREEN_HEIGHT, "msuarez- Wolf3D");
	if (env->win == (void *)0)
		return ;
	load_texture(env);
	env->old_dir_x = 0.0;
	env->old_plane_x = 0.0;
	env->texture = 0;
	env->flag_zero = 0;
	env->flag_one = 0;
	env->dir.x = -1;
	env->dir.y = 0;
	env->plane.x = 0;
	env->plane.y = 0.66;
	env->player.move_speed = 0.15;
	env->line_height = 0;
	env->wall_dist = 0.0;
}

static int		hook_close(t_env *env)
{
	(void)env;
	exit(0);
	return (0);
}

static int		validate_map(int ac, char **av, t_env *env)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (ac != 2)
	{
		ft_putendl("Wrong number of arguments!");
		ft_putendl("usage: ./wolf3d testmap");
		exit(0);
	}
	else if (fd < 0)
	{
		ft_putendl("The file is invalid or does not exist!");
		exit(0);
	}
	close(fd);
	parse_args(av[1], env);
	read_args(av[1], env);
	return (1);
}

void			raycast_init(t_env *env, int x)
{
	env->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	env->ray_dir.x = env->dir.x + env->plane.x * env->camera_x;
	env->ray_dir.y = env->dir.y + env->plane.y * env->camera_x;
	env->ray_pos.x = env->player.pos.x;
	env->ray_pos.y = env->player.pos.y;
	env->map.x = (int)env->ray_pos.x;
	env->map.y = (int)env->ray_pos.y;
	env->delta_dist.x = sqrt(1 + (env->ray_dir.y * env->ray_dir.y)
		/ (env->ray_dir.x * env->ray_dir.x));
	env->delta_dist.y = sqrt(1 + (env->ray_dir.x * env->ray_dir.x)
		/ (env->ray_dir.y * env->ray_dir.y));
	check_step(env);
	check_hit(env);
	if (env->side == 0)
		env->wall_dist = (env->map.x - env->ray_pos.x +
				(1 - env->step.x) / 2) / env->ray_dir.x;
	else
		env->wall_dist = (env->map.y - env->ray_pos.y +
				(1 - env->step.y) / 2) / env->ray_dir.y;
}

int				main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	if (validate_map(ac, av, env) == 1)
	{
		init_env(env);
		draw_world(env);
		mlx_hook(env->win, 2, 0, press_key, env);
		mlx_hook(env->win, 3, 0, release_key, env);
		mlx_hook(env->win, 17, 0, hook_close, env);
		mlx_loop_hook(env->mlx, event_key, env);
		mlx_loop(env->mlx);
	}
	return (0);
}
