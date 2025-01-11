/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recastinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 03:38:39 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-11 03:38:39 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player(t_mlx *mlx, t_map *map)
{
	mlx->move_speed = 3.0;
	mlx->rotation_speed = 0.05;
	mlx->map = map;
	mlx->flag = 0;

	if (map->start_direction == 'N')
		mlx->player_angle = 3 * M_PI / 2;
	else if (map->start_direction == 'S')
		mlx->player_angle = M_PI / 2;
	else if (map->start_direction == 'E')
		mlx->player_angle = 0;
	else if (map->start_direction == 'W')
		mlx->player_angle = M_PI;
}


void initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3d");
	if (!mlx->win)
		exit(1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(1);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
						 &mlx->line_lentgh, &mlx->endian);
	if (!mlx->addr)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(1);
	}
}