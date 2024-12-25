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

void	draw_pov(t_map *map, t_mlx *mlx)
{
    (void)map;

	int x_end_left, y_end_left;
	int x_end_right, y_end_right;
	int length = 100;
	double player_angle = 3 * M_PI / 2;

	calculate_endpoint(mlx, length, player_angle - M_PI / 6, &x_end_left, &y_end_left);
	calculate_endpoint(mlx, length, player_angle + M_PI / 6, &x_end_right, &y_end_right);
	draw_line_dda(mlx, mlx->player_x, mlx->player_y, x_end_left, y_end_left, 0xFF0000);
	draw_line_dda(mlx, mlx->player_x, mlx->player_y, x_end_right, y_end_right, 0xFF0000);
}