/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:56:05 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/09 17:18:28 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_env(t_env *env)
{
	if ((env->mlx = mlx_init()) == (void *)0)
		return ;
	env->win = mlx_new_window(env->mlx, SCREEN_WIDTH,
				SCREEN_HEIGHT, "Raycasting");
	if (env->win == (void *)0)
		return ;
	init_img(env);
	env->flag_zero = 0;
	env->flag_one = 0;
	env->dir.x = -1;
	env->dir.y = 0;
	env->plane.x = 0;
	env->plane.y = 0.66;
	env->player.move_speed = 0.15;
	env->thread_id = 0;
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

int				main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	if (validate_map(ac, av, env) == 1)
	{
		init_env(env);
		draw_again(env);
		mlx_hook(env->win, 2, 0, press_key, env);
		mlx_hook(env->win, 3, 0, release_key, env);
		mlx_hook(env->win, 17, 0, hook_close, env);
		mlx_loop_hook(env->mlx, event_key, env);
		mlx_loop(env->mlx);
	}
	return (0);
}
