/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-20 05:22:39 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-03-20 05:22:39 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int *get_pixels(unsigned char *img, int len) {
    
    unsigned int *ret = c_malloc((len / 4) * sizeof(unsigned int),1);
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

void choose_closest_hit(t_rays *ray, t_hit_points *hit, t_player *player)
{
    float horz_distance;
    float vert_distance;

    if (hit->found_horz)
        horz_distance = calculate_distance(player->x, player->y, hit->horz_x, hit->horz_y);
    else
        horz_distance = FLT_MAX;

    if (hit->found_vert)
        vert_distance = calculate_distance(player->x, player->y, hit->vert_x, hit->vert_y);
    else
        vert_distance = FLT_MAX;

    if (horz_distance < vert_distance)
    {
        ray->distance = horz_distance;
        ray->wallhitx = hit->horz_x;
        ray->wallhity = hit->horz_y;
        ray->hit_ver = 0;
    }
    else
    {
        ray->distance = vert_distance;
        ray->wallhitx = hit->vert_x;
        ray->wallhity = hit->vert_y;
        ray->hit_ver = 1;
    }
}

void finalize_ray(t_rays *ray, float ray_angle, float player_angle)
{
    ray->ray_angle = ray_angle;
    ray->distance *= cos(player_angle - ray_angle);
}