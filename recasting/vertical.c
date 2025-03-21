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

#include "../cub3D.h"

void	initialize_vert_params(t_mlx *mlx, t_rays *ray, t_ray_params *params)
{
	params->x_intercept = floor(mlx->player_x / mlx->range_ho_size)
		* mlx->range_ho_size;
	if (ray->facing_right)
		params->x_intercept += mlx->range_ho_size;
	params->y_intercept = mlx->player_y + (params->x_intercept - mlx->player_x)
		* tan(params->ray_angle);
	params->x_step = mlx->range_ho_size;
	if (ray->facing_left)
		params->x_step = -params->x_step;
}

void	calculate_vert_steps(t_rays *ray, t_ray_params *params)
{
	params->y_step = params->x_step * tan(params->ray_angle);
	if (ray->facing_up && params->y_step > 0)
		params->y_step = -params->y_step;
	else if (ray->facing_down && params->y_step < 0)
		params->y_step = -params->y_step;
}

void	find_vertical_hit(t_mlx *mlx, t_rays *ray, float ray_angle,
		t_hit_points *hit)
{
	float				next_x;
	float				next_y;
	int					map_x;
	int					map_y;
	t_ray_params		params;

	params.ray_angle = ray_angle;
	initialize_vert_params(mlx, ray, &params);
	calculate_vert_steps(ray, &params);
	next_x = params.x_intercept;
	next_y = params.y_intercept;
	hit->found_vert = 0;
	while (next_x >= 0 && next_x < ft_strlen(mlx->map->mp_arrs[0]) * 64
		&& next_y >= 0 && next_y < ft_strlen2d(mlx->map->mp_arrs) * 64)
	{
		if (ray->facing_left)
			map_x = (int)((next_x - 1) / mlx->range_ho_size);
		else
			map_x = (int)(next_x / mlx->range_ho_size);
		map_y = (int)(next_y / mlx->range_ve_size);
		if (map_y >= 0 && map_y < ft_strlen2d(mlx->map->mp_arrs)
			&& map_x >= 0 && map_x < ft_strlen(mlx->map->mp_arrs[0])
			&& mlx->map->mp_arrs[map_y][map_x] == '1')
		{
			hit->vert_x = next_x;
			hit->vert_y = next_y;
			hit->found_vert = 1;
			break ;
		}
		next_x += params.x_step;
		next_y += params.y_step;
	}
}
