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

void	draw_grid(t_mlx *mlx, int cell_width, int cell_height)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(mlx, x, y, 0xff0000);
			y++;
		}
		x += cell_width;
	}
	y = 0;
	while (y <= HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, x, y, 0xff0000);
			x++;
		}
		y += cell_height;
	}
}

void	draw2d(t_map *map, t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	mlx->range_ho_size = 64;
	mlx->range_ve_size = 64;
	while (map->mp_arrs[y])
	{
		x = 0;
		while (map->mp_arrs[y][x])
		{
			if (map->mp_arrs[y][x] == '0' || map->mp_arrs[y][x] == 'W' ||
					map->mp_arrs[y][x] == 'E' || map->mp_arrs[y][x] == 'S' ||
						map->mp_arrs[y][x] == 'N')
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
			}
			x++;
		}
		y++;
	}
}
