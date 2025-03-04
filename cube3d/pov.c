/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-25 12:38:46 by kaafkhar          #+#    #+#             */
/*   Updated: 2024-12-25 12:38:46 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	calculate_steps(int x0, int y0, int x1, int y1)
{
	float	dx;
	float	dy;

	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		return fabs(dx);
	return fabs(dy);
}


void	draw_pixel(t_mlx *mlx, float x, float y, int color)
{
    printf("hello\n");
if (round(x) >= 0 && round(x) < WIDTH && round(y) >= 0 && round(y) < HEIGHT)
		my_mlx_pixel_put(mlx, round(x), round(y), color);
}

void	draw_line_pixels(t_mlx *mlx, float x0, float y0, float x1, float y1, int steps, int color)
{
	float	x;
	float	y;
	float	increment_x;
	float	increment_y;

	x = x0;
	y = y0;
	increment_x = (x1 - x0) / steps;
	increment_y = (y1 - y0) / steps;
	while (steps-- >= 0)
	{
		draw_pixel(mlx, x, y, color);
		x += increment_x;
		y += increment_y;
	}
}

void	draw_line_dda(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int steps = calculate_steps(x0, y0, x1, y1);

    if (steps == 0)
    {
        draw_pixel(mlx, x0, y0, color);
        return;
    }

    draw_line_pixels(mlx, x0, y0, x1, y1, steps, color);
}

void	calculate_endpoint(t_mlx *mlx, int length, double angle, int *x_end, int *y_end)
{
    *x_end = mlx->player_x + (int)(length * cos(angle));
    *y_end = mlx->player_y + (int)(length * sin(angle));
}

void check_wall_collision(t_map *map, t_mlx *mlx, double start_x, double start_y, double angle, 
                         double *collision_x, double *collision_y)
{
    double ray_x = start_x;
    double ray_y = start_y;
    double dx = cos(angle);
    double dy = sin(angle);
    double step = 1.0;

    while (1)
    {
        int map_x = (int)(ray_x / mlx->range_ho_size);
        int map_y = (int)(ray_y / mlx->range_ve_size);

        if (map_x < 0 || map_x >= WIDTH  || map_y < 0 || map_y >= HEIGHT)
            break;
        if (map->mp_arrs[map_y][map_x] == '1')
            break;
        ray_x += dx * step;
        ray_y += dy * step;
    }

    *collision_x = ray_x;
    *collision_y = ray_y;
}

void draw_pov(t_map *map, t_mlx *mlx)
{
    double fov = M_PI / 3;
    int num_rays = 60;
    double angle_step = fov / (num_rays - 1);
    double start_angle = mlx->player_angle - fov/2;
    int i = 0;
    double collision_x, collision_y;
    double current_angle;

    while (i < num_rays)
    {
        current_angle = start_angle + (i * angle_step);
        check_wall_collision(map, mlx, mlx->player_x, mlx->player_y, 
                           current_angle, &collision_x, &collision_y);
        draw_line_dda(mlx, mlx->player_x, mlx->player_y, 
                     (int)collision_x, (int)collision_y, 0x550000);
        i++;
    }
}
