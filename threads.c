/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 14:16:53 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/09 15:41:09 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		copy_node(t_env *copy, t_env *node, int i)
{
	ft_memcpy(copy, node, sizeof(t_env));
	copy->thread_id = i;
}

static void		*call_draw(void *data)
{
	t_env	*node;

	node = (t_env *)data;
	draw_world(node);
	return (NULL);
}

void			draw_again(t_env *env)
{
	pthread_t	*threads;
	t_env		*copies[THREADS];
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * THREADS);
	clear_img(env);
	while (i < THREADS)
	{
		copies[i] = (t_env *)malloc(sizeof(t_env));
		copy_node(copies[i], env, i);
		pthread_create(&threads[i], NULL, call_draw, copies[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		free(copies[i]);
		i++;
	}
	free(threads);
	mlx_put_image_to_window(env->mlx, env->win, env->img.image, 0, 0);
}
