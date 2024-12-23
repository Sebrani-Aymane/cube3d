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

int	ft_strlen2d(char **str)
{
	int i;

	i = 0;
	while(str[i] != NULL)
		i++;
	return(i);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_lentgh + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	draw2d(t_map *map, t_mlx *mlx)
{
	int	range_ho_size = WIDTH / (ft_strlen(map->mp_arrs[0]));
	int	range_ve_size = HEIGHT / (ft_strlen2d(map->mp_arrs));
	int	y = 0;
	int	x;
	int	i ; 
	int	j ;

	i = 0;
	j = 0;
	while (map->mp_arrs[y] != NULL)
	{
		x = 0; 
		while (map->mp_arrs[y][x])
		{
			if (map->mp_arrs[y][x] == '1')
			{
				while(i < range_ve_size)
				{
					j = 0;
					while(j < range_ho_size)
					{
						my_mlx_pixel_put(mlx, x * range_ho_size + j, y * range_ve_size + i, 0x000000);
						j++;
					}
					i++;
				}
			}
			else if (map->mp_arrs[y][x] == '0'  || map->mp_arrs[y][x] == 'W' || map->mp_arrs[y][x] == 'E' || map->mp_arrs[y][x] == 'S' || map->mp_arrs[y][x] == 'N')
			{
				i = 0;
				while(i < range_ve_size)
				{
					j = 0;
					while(j < range_ho_size)
					{
					    my_mlx_pixel_put(mlx, x * range_ho_size + j, y * range_ve_size + i, 0xFFFFFF);
					    j++;
					}
					i++;
				}
				if (map->mp_arrs[y][x] == 'W' || map->mp_arrs[y][x] == 'E' || map->mp_arrs[y][x] == 'S' || map->mp_arrs[y][x] == 'N')
				{
					int player_x = x * range_ho_size + range_ho_size / 2;
					int player_y = y * range_ve_size + range_ve_size / 2;
					my_mlx_pixel_put(mlx, player_x, player_y, 0xff0000);
					my_mlx_pixel_put(mlx, player_x-1, player_y-1, 0xff0000);
					my_mlx_pixel_put(mlx, player_x+1, player_y+1, 0xff0000);
					my_mlx_pixel_put(mlx, player_x+1, player_y-1, 0xff0000);
					my_mlx_pixel_put(mlx, player_x-1, player_y+1, 0xff0000);
					my_mlx_pixel_put(mlx, player_x-2, player_y-2, 0xff0000);
					my_mlx_pixel_put(mlx, player_x+2, player_y+2, 0xff0000);
					my_mlx_pixel_put(mlx, player_x+2, player_y-2, 0xff0000);
					my_mlx_pixel_put(mlx, player_x-2, player_y+2, 0xff0000);
				}
			}
			x++;
		}
		y++;
	}
}

int handle_keys(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return 0;

}

int	close_wind(t_mlx *mlx)
{
	
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
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
	draw_grid(mlx, range_ho_size, range_ve_size);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_hook(mlx->win, 17, 0, close_wind, mlx);
	mlx_key_hook(mlx->win, handle_keys, mlx);
	mlx_loop(mlx->mlx);
}