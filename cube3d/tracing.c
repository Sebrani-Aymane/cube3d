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

void render_frame(t_mlx *mlx)
{
   int total_bytes = WIDTH * HEIGHT * (mlx->bits_per_pixel / 8);
   for (int i = 0; i < total_bytes; i++)
        mlx->addr[i] = 0;
   
   draw2d(mlx->map, mlx);
	my_mlx_pixel_put(mlx, mlx->player_x, mlx->player_y, 0xff0000);
    draw_grid(mlx, mlx->range_ho_size, mlx->range_ve_size);
    draw_pov(mlx->map, mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int is_valid_position(t_mlx *mlx, int new_x, int new_y)
{
    int map_x = new_x / mlx->range_ho_size;
    int map_y = new_y / mlx->range_ve_size;
    
    if (map_x < 0 || map_y < 0 || map_y >= ft_strlen2d(mlx->map->mp_arrs) || 
        map_x >= ft_strlen(mlx->map->mp_arrs[map_y]))
        return 0;
        
    return (mlx->map->mp_arrs[map_y][map_x] != '1');
}


void rotate_player(t_mlx *mlx, int clockwise)
{
    if (clockwise)
        mlx->player_angle += mlx->rotation_speed;
    else
        mlx->player_angle -= mlx->rotation_speed;
        
    mlx->player_angle = fmod(mlx->player_angle, 2 * M_PI);
    if (mlx->player_angle < 0)
        mlx->player_angle += 2 * M_PI;
        
    render_frame(mlx);
}

void move_player(t_mlx *mlx, int forward)
{
	double move_angle = mlx->player_angle;
	double move_speed = mlx->move_speed;
	int new_x, new_y;

   if (!forward)
   {
        move_angle += M_PI;
        move_speed = move_speed * 0.8;
	}
    double dx = cos(move_angle) * move_speed;
    double dy = sin(move_angle) * move_speed;

    new_x = mlx->player_x + (int)dx;
    new_y = mlx->player_y + (int)dy;

   
    if (is_valid_position(mlx, new_x, mlx->player_y))
        mlx->player_x = new_x;
    if (is_valid_position(mlx, mlx->player_x, new_y))
        mlx->player_y = new_y;
    
    render_frame(mlx);
}


void	initialize_map_settings(t_map *map, t_mlx *mlx)
{
	mlx->range_ho_size = WIDTH / ft_strlen(map->mp_arrs[0]);
	mlx->range_ve_size = HEIGHT / ft_strlen2d(map->mp_arrs);
	init_player(mlx, map);
}

void setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, close_wind, mlx);
	mlx_loop_hook(mlx->mlx, game_loop, mlx);

}

void map_tracing(t_map *map, t_mlx *mlx)
{
	initialize_mlx(mlx);
	mlx->keys = (t_keys){0, 0, 0, 0, 0, 0};

	initialize_map_settings(map, mlx);
	render_frame(mlx);
	setup_hooks(mlx);
	mlx_loop(mlx->mlx);
}