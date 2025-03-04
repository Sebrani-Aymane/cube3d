/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:13:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/04 02:53:04 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include <libc.h>
unsigned int *get_pixels(unsigned char *img, int len) {
    
    unsigned int *ret = malloc((len / 4) * sizeof(unsigned int));
    if (!ret) return NULL;  

    int i = 0;
    int t = 0;
    while (i < len) {
    unsigned int temp = 0;
    temp |= (unsigned int)img[i++];      
    temp |= (unsigned int)img[i++] << 8;  
    temp |= (unsigned int)img[i++] << 16;
    temp |= (unsigned int)img[i++] << 24; 
    ret[t++] = temp;
    }

    return ret;
}

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
void print_map(char **map)
{
	while(*map)
	{
		printf("|%s|%d\n",*(map),ft_strlen(*map));
		map++;
	}
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

    t_texture *texture = &mlx->texs.north;
    while (strip_id < NUM_RAYS)
    {
        double tex_x;
        if(mlx->rays[strip_id].hit_ver)
        {
            tex_x = fmod(mlx->rays[strip_id].wallhity, 64);
            if(mlx->rays[strip_id].facing_left)
                texture = &mlx->texs.west;
            else
                texture = &mlx->texs.east;
        }
        else
        {
            tex_x = fmod(mlx->rays[strip_id].wallhitx, 64);
            if(mlx->rays[strip_id].facing_down)
                texture = &mlx->texs.south;
            else
                texture = &mlx->texs.north;
        }
        tex_x = (tex_x * texture->width) / 64;
        if(mlx->rays[strip_id].hit_ver && mlx->rays[strip_id].facing_left)
            tex_x = texture->width - tex_x;
        if(!mlx->rays[strip_id].hit_ver && mlx->rays[strip_id].facing_down)
             tex_x = texture->width - tex_x;
        perpDistance = mlx->rays[strip_id].distance;
        if (perpDistance < 1) perpDistance = 1;
        wall_height = (mlx->range_ve_size * HEIGHT) / perpDistance;
        //  if (wall_height  > HEIGHT * 5)
        //      wall_height  = HEIGHT * 5;
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        wall_bottom = (HEIGHT / 2) + (wall_height / 2);
        double tex_offset = (double)texture->height / wall_height;
        int y = 0;
        while (y < wall_top)
        {
           my_mlx_pixel_put(mlx, strip_id, y, mlx->ceiling_color);
            y++;
        }
        y = wall_top;
        while (y < wall_bottom)
        {
            int tex_y = (y - wall_top) * tex_offset;
            color = get_texture_color(texture,tex_x,tex_y);
            if(wall_height  == HEIGHT * 4)
                color = 0;
            my_mlx_pixel_put(mlx, strip_id, y, color);
             y++;
        }
        y = wall_bottom;
        while (y < HEIGHT)
        {

            my_mlx_pixel_put(mlx, strip_id, y, mlx->floor_color);
            y++;
        }
        strip_id++;
    }
}

