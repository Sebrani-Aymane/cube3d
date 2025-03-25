/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:52:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/04 02:41:32 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	initialize_cell_sizes(t_mlx *mlx)
{
	mlx->range_ho_size = 64;
	mlx->range_ve_size = 64;
}

void	set_player_position(t_map *map, t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (map->mp_arrs[y])
	{
		x = 0;
		while (map->mp_arrs[y][x])
		{
			if (map->mp_arrs[y][x] == 'W' || map->mp_arrs[y][x] == 'E' ||
				map->mp_arrs[y][x] == 'S' || map->mp_arrs[y][x] == 'N')
			{
				if (mlx->flag == 0)
				{
					mlx->player_x = x * mlx->range_ho_size
						+ mlx->range_ho_size / 2;
					mlx->player_y = y * mlx->range_ve_size
						+ mlx->range_ve_size / 2;
					mlx->flag = 1;
				}
			}
			x++;
		}
		y++;
	}
}

void	place_player(t_map *map, t_mlx *mlx)
{
	initialize_cell_sizes(mlx);
	set_player_position(map, mlx);
}
