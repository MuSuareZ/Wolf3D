/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:39:00 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/01 15:36:28 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft/libft.h"

# define ESC 53
# define screenWidth 1000
# define screenHeight 1000

# define W 13
# define S 1
# define A 0
# define D 2

# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125

typedef	struct	s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;


typedef struct	s_image
{
	void	*image;
	char	*ptr;
	int		bpp;
	int		line_s;
	int		endian;
}				t_image;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_coord	mouse;

	int		map_width;
	int		map_height;
	int		draw_start;
	int		draw_end;
	int		flag_zero;
	int		flag_one;
	int		side;
	int		hit;
	int		color;
	double	move_speed;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	t_point	map;
	t_point	step;
	t_coord	delta_dist;
	t_coord	ray_dir;
	t_coord	side_dist;
	t_coord pos;
	t_coord dir;
	t_coord plane;
	int		**world_map;
}				t_env;

int		get_width(char *filepath);
int		get_height(char *filepath);
void	read_args(char *filepath, t_env *env);
void	parse_args(char *filepath, t_env *env);

int		event_key(t_env *env);
int		press_key(int keycode, t_env *env);
int		release_key(int keycode, t_env *env);
int		mouse_move(int x, int y, t_env *e);
void	exit_error(int n);
void	draw_world(t_env *env);
void	clear_img(t_env *env);
void	img_pixel_put(t_env *env, double x, double y, int color);
void	init_img(t_env *env);
void	draw_again(t_env *env);

#endif
