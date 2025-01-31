/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 23:13:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-11 23:13:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void choose_closest_hit(t_rays *ray, float horz_x, float horz_y, float vert_x, float vert_y,
                            int found_horz, int found_vert, float player_x, float player_y)
{
    float horz_distance;
    if (found_horz)
    {
        horz_distance = calculate_distance(player_x, player_y, horz_x, horz_y);
    }
    else
    {
        horz_distance = FLT_MAX;
    }
    float vert_distance;
    if (found_vert)
    {
        vert_distance = calculate_distance(player_x, player_y, vert_x, vert_y);
    }
    else
    {
        vert_distance = FLT_MAX;
    }

    if (horz_distance < vert_distance)
    {
        ray->distance = horz_distance;
        ray->wallhitx = horz_x;
        ray->wallhity = horz_y;
        ray->hit_ver = 0;
    }
    else
    {
        ray->distance = vert_distance;
        ray->wallhitx = vert_x;
        ray->wallhity = vert_y;
        ray->hit_ver = 1;
    }
}

void finalize_ray(t_rays *ray, float ray_angle, float player_angle)
{
    ray->ray_angle = ray_angle;
    ray->distance *= cos(player_angle - ray_angle);
}

void cast_rays(t_mlx *mlx)
{
    float ray_angle;
    int strip_id;

    strip_id = 0;
    ray_angle = mlx->player_angle - (FOV_ANGLE / 2);
    while (strip_id < NUM_RAYS)
    {
        ray_angle = normal_angle(ray_angle);
        t_rays *ray = &mlx->rays[strip_id];
        initialize_ray(ray, ray_angle);

        float horz_x = 0, horz_y = 0, vert_x = 0, vert_y = 0;
        int found_horz = 0, found_vert = 0;

        find_horizontal_hit(mlx, ray, ray_angle, &horz_x, &horz_y, &found_horz);
        find_vertical_hit(mlx, ray, ray_angle, &vert_x, &vert_y, &found_vert);

        choose_closest_hit(ray, horz_x, horz_y, vert_x, vert_y, found_horz, found_vert, mlx->player_x, mlx->player_y);
        finalize_ray(ray, ray_angle, mlx->player_angle);

        ray_angle += FOV_ANGLE / NUM_RAYS;
        strip_id++;
    }
}

void draw_walls(t_mlx *mlx)
{
    int strip_id = 0;
    int wall_top;
    int wall_bottom;
    float wall_height;
    float perpDistance;
    int color;

    while (strip_id < NUM_RAYS)
    {
        perpDistance = mlx->rays[strip_id].distance;
        if (perpDistance < 1) perpDistance = 1;
        wall_height = (mlx->range_ve_size * HEIGHT) / perpDistance;
        if (wall_height > HEIGHT * 3)
            wall_height = HEIGHT * 3;
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        wall_top = wall_top < 0 ? 0 : wall_top;
        wall_bottom = (HEIGHT / 2) + (wall_height / 2);
        wall_bottom = wall_bottom > HEIGHT ? HEIGHT : wall_bottom;

        int y = 0;
        while (y < wall_top)
        {
            my_mlx_pixel_put(mlx, strip_id, y, 0xff00000);
            y++;
        }

        color = mlx->rays[strip_id].hit_ver ? 0x8800aa : 0x909090;
        y = wall_top;
        while (y < wall_bottom)
        {
            my_mlx_pixel_put(mlx, strip_id, y, mlx->addr[1]);
             y++;
        }

        y = wall_bottom;
        while (y < HEIGHT)
        {
            my_mlx_pixel_put(mlx, strip_id, y, 0x654321);
            y++;
        }

        strip_id++;
    }
}
