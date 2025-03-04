/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:47:12 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/04 02:13:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float normal_angle(float angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

void initialize_ray(t_rays *ray, float ray_angle)
{
    ray->facing_down = ray_angle > 0 && ray_angle < M_PI;
    ray->facing_up = !ray->facing_down;
    ray->facing_right = ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2;
    ray->facing_left = !ray->facing_right;
}

void find_horizontal_hit(t_mlx *mlx, t_rays *ray, float ray_angle, float *horz_x, float *horz_y, int *found)
{
    float y_intercept;
    float x_intercept;
    float y_step;
    float x_step;
    float next_x;
    float next_y;

    y_intercept = floor(mlx->player_y / mlx->range_ve_size) * mlx->range_ve_size;
    if (ray->facing_down)
    {
        y_intercept += mlx->range_ve_size;
    }
    x_intercept = mlx->player_x + (y_intercept - mlx->player_y) / tan(ray_angle);
    if (ray->facing_up)
    {
        y_step = -mlx->range_ve_size;
    }
    else
    {
        y_step = mlx->range_ve_size;
    }
    x_step = mlx->range_ve_size / tan(ray_angle);
    if (ray->facing_left && x_step > 0)
    {
        x_step = -x_step;
    }
    else if (ray->facing_right && x_step < 0)
    {
        x_step = -x_step;
    }
    next_x = x_intercept;
    next_y = y_intercept;
    *found = 0;
    while (next_x >= 0 && next_x <ft_strlen(mlx->map->mp_arrs[0]) * 64 && next_y >= 0 && next_y < ft_strlen2d(mlx->map->mp_arrs) * 64)
    {
        int map_x = (int)(next_x / mlx->range_ho_size);
        int map_y;
        if (ray->facing_up)
        {
            map_y = (int)((next_y - 1) / mlx->range_ve_size);
        }
        else
        {
            map_y = (int)(next_y / mlx->range_ve_size);
        }

        if (map_y >= 0 && map_y < ft_strlen2d(mlx->map->mp_arrs) &&
            map_x >= 0 && map_x < ft_strlen(mlx->map->mp_arrs[0]) &&
            mlx->map->mp_arrs[map_y][map_x] == '1')
        {
            *horz_x = next_x;
            *horz_y = next_y;
            *found = 1;
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
}

void find_vertical_hit(t_mlx *mlx, t_rays *ray, float ray_angle, float *vert_x, float *vert_y, int *found)
{
    float x_intercept;
    float y_intercept;
    float x_step;
    float y_step;
    float next_x;
    float next_y;
    
    x_intercept= floor(mlx->player_x / mlx->range_ho_size) * mlx->range_ho_size;
    if (ray->facing_right)
    {
        x_intercept += mlx->range_ho_size;
    }
    y_intercept = mlx->player_y + (x_intercept - mlx->player_x) * tan(ray_angle);
    x_step = mlx->range_ho_size;
    if (ray->facing_left)
    {
        x_step = -x_step;
    }
    y_step = mlx->range_ho_size * tan(ray_angle);
    if (ray->facing_up && y_step > 0)
    {
        y_step = -y_step;
    }
    else if (ray->facing_down && y_step < 0)
    {
        y_step = -y_step;
    }
    next_x = x_intercept;
    next_y = y_intercept;
    *found = 0; 
    while (next_x >= 0 && next_x < ft_strlen(mlx->map->mp_arrs[0]) * 64 && next_y >= 0 && next_y < ft_strlen2d(mlx->map->mp_arrs) * 64)
    {
        int map_x;

        if (ray->facing_left)
        {
            map_x = (int)((next_x - 1) / mlx->range_ho_size);
        }
        else
        {
            map_x = (int)(next_x / mlx->range_ho_size);
        }

        int map_y = (int)(next_y / mlx->range_ve_size);
        if (map_y >= 0 && map_y < ft_strlen2d(mlx->map->mp_arrs) &&
            map_x >= 0 && map_x < ft_strlen(mlx->map->mp_arrs[0]) &&
            mlx->map->mp_arrs[map_y][map_x] == '1')
        {
            *vert_x = next_x;
            *vert_y = next_y;
            *found = 1;
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
}