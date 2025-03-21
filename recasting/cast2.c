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

unsigned int	convert_bytes_to_int(unsigned char *img, int *i)
{
	unsigned int	byte1;
	unsigned int	byte2;
	unsigned int	byte3;
	unsigned int	byte4;

	byte1 = (unsigned int)img[*i++];
	byte2 = (unsigned int)img[*i++] << 8;
	byte3 = (unsigned int)img[*i++] << 16;
	byte4 = (unsigned int)img[*i++] << 24;
	return (byte1 | byte2 | byte3 | byte4);
}

unsigned int	*get_pixels(unsigned char *img, int len)
{
	int				i;
	int				t;
	unsigned int	*ret;

	if (!img || len % 4 != 0)
		return (NULL);
	ret = c_malloc((len / 4) * sizeof(unsigned int), 1);
	if (!ret)
		return (NULL);
	i = 0;
	t = 0;
	while (i < len)
	{
		ret[t++] = convert_bytes_to_int(img, &i);
	}
	return (ret);
}

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

void	choose_closest_hit(t_rays *ray, t_hit_points *hit, t_player *player)
{
	float	horz_distance;
	float	vert_distance;

	horz_distance = FLT_MAX;
	vert_distance = FLT_MAX;
	if (hit->found_horz)
		horz_distance = calculate_distance(player->x, player->y,
				hit->horz_x, hit->horz_y);
	if (hit->found_vert)
		vert_distance = calculate_distance(player->x, player->y,
				hit->vert_x, hit->vert_y);
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
	if (ray->distance < 0.1)
		ray->distance = 0.1;
}

void	finalize_ray(t_rays *ray, float ray_angle, float player_angle)
{
	ray->ray_angle = ray_angle;
	ray->distance *= cosf(player_angle - ray_angle);
}
