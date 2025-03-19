/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recastinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:38:39 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/04 02:01:50 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_player_rays(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		mlx->rays[i].distance = 0;
		mlx->rays[i].ray_angle = 0;
		mlx->rays[i].wallhitx = 0;
		mlx->rays[i].wallhity = 0;
		mlx->rays[i].hit_ver = 0;
		mlx->rays[i].facing_up = 0;
		mlx->rays[i].facing_down = 0;
		mlx->rays[i].facing_left = 0;
		mlx->rays[i].facing_right = 0;
		i++;
	}
}

void	init_player(t_mlx *mlx, t_map *map)
{
	mlx->move_speed = 3.0;
	mlx->rotation_speed = 0.05;
	mlx->map = map;
	mlx->flag = 0;
	init_player_rays(mlx);
	if (map->start_direction == 'N')
		mlx->player_angle = 3 * M_PI / 2;
	else if (map->start_direction == 'S')
		mlx->player_angle = M_PI / 2;
	else if (map->start_direction == 'E')
		mlx->player_angle = 0;
	else if (map->start_direction == 'W')
		mlx->player_angle = M_PI;
}

void	initialize_map_settings(t_map *map, t_mlx *mlx)
{
	mlx->range_ho_size = 64;
	mlx->range_ve_size = 64;
	init_player(mlx, map);
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3D");
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
