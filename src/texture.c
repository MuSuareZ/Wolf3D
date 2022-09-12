/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:13:59 by msuarez-          #+#    #+#             */
/*   Updated: 2020/07/21 17:21:14 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		load_textures3(t_env *env, int a, int b)
{
	env->tex[9].image =
		mlx_xpm_file_to_image(env->mlx, "texture/colorstone.xpm", &a, &b);
	env->tex[9].ptr = mlx_get_data_addr(env->tex[9].image, &env->tex[9].bpp,
		&env->tex[9].line_s, &env->tex[9].endian);
	a = 512;
	b = 512;
	env->tex[6].image =
		mlx_xpm_file_to_image(env->mlx, "texture/sky.xpm", &a, &b);
	env->tex[6].ptr = mlx_get_data_addr(env->tex[6].image, &env->tex[6].bpp,
		&env->tex[6].line_s, &env->tex[6].endian);
}

static void		load_textures2(t_env *env, int a, int b)
{
	env->tex[5].image =
		mlx_xpm_file_to_image(env->mlx, "texture/stone5.xpm", &a, &b);
	env->tex[5].ptr = mlx_get_data_addr(env->tex[5].image, &env->tex[5].bpp,
		&env->tex[5].line_s, &env->tex[5].endian);
	env->tex[7].image =
		mlx_xpm_file_to_image(env->mlx, "texture/sand.xpm", &a, &b);
	env->tex[7].ptr = mlx_get_data_addr(env->tex[7].image, &env->tex[7].bpp,
		&env->tex[7].line_s, &env->tex[7].endian);
	env->tex[8].image =
		mlx_xpm_file_to_image(env->mlx, "texture/metal.xpm", &a, &b);
	env->tex[8].ptr = mlx_get_data_addr(env->tex[8].image, &env->tex[8].bpp,
		&env->tex[8].line_s, &env->tex[8].endian);
	load_textures3(env, a, b);
}

void			load_texture(t_env *env)
{
	int		a;
	int		b;

	a = 64;
	b = 64;
	env->tex[1].image =
		mlx_xpm_file_to_image(env->mlx, "texture/stone2.xpm", &a, &b);
	env->tex[1].ptr = mlx_get_data_addr(env->tex[1].image, &env->tex[1].bpp,
		&env->tex[1].line_s, &env->tex[1].endian);
	env->tex[2].image =
		mlx_xpm_file_to_image(env->mlx, "texture/wood.xpm", &a, &b);
	env->tex[2].ptr = mlx_get_data_addr(env->tex[2].image, &env->tex[2].bpp,
			&env->tex[2].line_s, &env->tex[2].endian);
	env->tex[3].image =
		mlx_xpm_file_to_image(env->mlx, "texture/mossy.xpm", &a, &b);
	env->tex[3].ptr = mlx_get_data_addr(env->tex[3].image, &env->tex[3].bpp,
			&env->tex[3].line_s, &env->tex[3].endian);
	env->tex[4].image =
		mlx_xpm_file_to_image(env->mlx, "texture/sand.xpm", &a, &b);
	env->tex[4].ptr = mlx_get_data_addr(env->tex[4].image, &env->tex[4].bpp,
			&env->tex[4].line_s, &env->tex[4].endian);
	load_textures2(env, a, b);
}
