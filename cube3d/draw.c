/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-12 00:52:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-12 00:52:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
			my_mlx_pixel_put(mlx, x, y, 0x00FF00);
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
			my_mlx_pixel_put(mlx, x, y, 0x00FF00);
			x++;
		}
		y += cell_height;
	}
}

void	draw_tile(t_mlx *mlx, int x, int y, int range_ho_size, int range_ve_size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < range_ve_size)
	{
	j = 0;
	while (j < range_ho_size)
	{
		my_mlx_pixel_put(mlx, x * range_ho_size + j, y * range_ve_size + i, color);
		j++;
	}
	i++;
	}
}

void	draw2d(t_map *map, t_mlx *mlx)
{
    int y;
	int x;

	y = 0;
	mlx->range_ho_size = WIDTH / (ft_strlen(map->mp_arrs[0]));
	mlx->range_ve_size = HEIGHT / (ft_strlen2d(map->mp_arrs));
	while (map->mp_arrs[y] != NULL)
	{
		x = 0;
		while (map->mp_arrs[y][x])
		{
			if (map->mp_arrs[y][x] == '1')
				draw_tile(mlx, x, y, mlx->range_ho_size, mlx->range_ve_size, 0x000000);
			else if (map->mp_arrs[y][x] == '0' || map->mp_arrs[y][x] == 'W' ||
					map->mp_arrs[y][x] == 'E' || map->mp_arrs[y][x] == 'S' || map->mp_arrs[y][x] == 'N')
			{
				draw_tile(mlx, x, y, mlx->range_ho_size, mlx->range_ve_size, 0xFFFFFF);
				if (map->mp_arrs[y][x] == 'W' || map->mp_arrs[y][x] == 'E' ||
					map->mp_arrs[y][x] == 'S' || map->mp_arrs[y][x] == 'N')
					{
						if (mlx->flag == 0)
						{
							mlx->player_x = x * mlx->range_ho_size + mlx->range_ho_size / 2;
							mlx->player_y = y * mlx->range_ve_size + mlx->range_ve_size / 2;
							mlx->flag = 1;
						}
					}
			}
			x++;
		}
		y++;
	}
}
