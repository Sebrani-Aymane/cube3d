/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-21 03:17:02 by kaafkhar          #+#    #+#             */
/*   Updated: 2024-12-21 03:17:02 by kaafkhar         ###   ########.fr       */
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

void	draw_player(t_mlx *mlx, int x, int y)
{
	mlx->player_x = x * mlx->range_ho_size + mlx->range_ho_size / 2;
	mlx->player_y = y * mlx->range_ve_size + mlx->range_ve_size / 2;
	my_mlx_pixel_put(mlx, mlx->player_x, mlx->player_y, 0xff0000);
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
					draw_player(mlx, x, y);
			}
			x++;
		}
		y++;
	}
}

void	map_tracing(t_map *map, t_mlx *mlx)
{
	(void)map;
	int range_ho_size; 
	int range_ve_size; 

	range_ho_size = WIDTH / (ft_strlen(map->mp_arrs[0]));
	range_ve_size = HEIGHT / (ft_strlen2d(map->mp_arrs));

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
	draw2d(map, mlx);
	draw_grid(mlx, mlx->range_ho_size, mlx->range_ve_size);
	printer(map->mp_arrs);
	draw_pov(map, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_hook(mlx->win, 17, 0, close_wind, mlx);
	mlx_key_hook(mlx->win, handle_keys, mlx);
	mlx_loop(mlx->mlx);
}