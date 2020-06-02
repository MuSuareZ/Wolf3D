/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:32:37 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/02 16:00:48 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			parse_args(char *filepath, t_env *env)
{
	int	index;

	index = 0;
	env->map_height = get_height(filepath);
	env->map_width = get_width(filepath);
	env->world_map = (int **)malloc(sizeof(int *) * env->map_height);
	while (index < env->map_height)
	{
		env->world_map[index] = (int *)malloc(sizeof(int) * env->map_width);
		index++;
	}
}

static void		check_mid(t_env *env)
{
	int		y;
	int		limit;

	y = 0;
	limit = env->map_width - 1;
	while (y < env->map_height - 1)
	{
		if (env->world_map[y][0] == 0 || env->world_map[y][limit] == 0)
			exit_error(3);
		else
			y++;
	}
}

static void		check_bottom(t_env *env)
{
	int		limit;
	int			x;

	x = 0;
	limit = env->map_height - 1;
	while (x < env->map_width)
	{
		if (env->world_map[limit][x] == 0)
			exit_error(3);
		else
			x++;
	}
}

static void		assign_z(int x, int y, char **line_split, t_env *env)
{
	
	while (*line_split != NULL)
	{
		env->world_map[y][x] = ft_atoi(*line_split);
		if (env->world_map[0][x] == 0)
			exit_error(3);
		if (env->world_map[y][x] == 1)
			env->flag_one = 1;
		if (env->flag_zero == 0 && env->world_map[y][x] == 0)
		{
			env->pos.x = x + 0.5;
			env->pos.y = y + 0.5;
			env->flag_zero = 1;
		}
		free(*line_split);
		x++;
		line_split++;
	}
}

void			read_args(char *filepath, t_env *env)
{
	char	*line;
	char	**line_split;
	int		fd;
	int		x;
	int		y;

	x = 0;
	y = 0;
	fd = open(filepath, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		line_split = ft_strsplit(line, ' ');
		assign_z(x, y, line_split, env);
		free(line);
		line_split -= x;
		x = 0;
		y++;
		free(line_split);
	}
	check_mid(env);
	check_bottom(env);
	if (env->flag_zero == 0 || env->flag_one == 0)
		exit_error(2);
	close(fd);
}
