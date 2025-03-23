/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:42:28 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/23 10:07:31 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	initialize_horz_params(t_mlx *mlx, t_rays *ray, t_horz_params *params)
{
	params->y_intercept = floor(mlx->player_y / mlx->range_ve_size)
		* mlx->range_ve_size;
	if (ray->facing_down)
		params->y_intercept += mlx->range_ve_size;
	params->x_intercept = mlx->player_x + (params->y_intercept - mlx->player_y)
		/ tan(params->ray_angle);
	if (ray->facing_up)
		params->y_step = -mlx->range_ve_size;
	else
		params->y_step = mlx->range_ve_size;
}

void	calculate_horz_steps(t_rays *ray, t_mlx *mlx, t_horz_params *params)
{
	params->x_step = mlx->range_ve_size / tan(params->ray_angle);
	if (ray->facing_left && params->x_step > 0)
		params->x_step = -params->x_step;
	else if (ray->facing_right && params->x_step < 0)
		params->x_step = -params->x_step;
}

void	initialize_horz_hit(t_mlx *mlx, t_rays *ray,
		t_horz_params *params, float ray_angle)
{
	params->ray_angle = ray_angle;
	initialize_horz_params(mlx, ray, params);
	calculate_horz_steps(ray, mlx, params);
}

void	find_horizontal_hit(t_mlx *mlx, t_rays *ray, float ray_angle,
		t_hit_points *hit)
{
	float			next_x;
	float			next_y;
	int				map_x;
	int				map_y;
	t_horz_params	params;

	initialize_horz_hit(mlx, ray, &params, ray_angle);
	next_x = params.x_intercept;
	next_y = params.y_intercept;
	hit->found_horz = 0;
	while (next_x >= 0 && next_x < ft_strlen(mlx->map->mp_arrs[0]) * 64
		&& next_y >= 0 && next_y < ft_strlen2d(mlx->map->mp_arrs) * 64)
	{
		map_x = (int)(next_x / mlx->range_ho_size);
		if (ray->facing_up)
			map_y = (int)((next_y - 1) / mlx->range_ve_size);
		else
			map_y = (int)(next_y / mlx->range_ve_size);
		if (map_y >= 0 && map_y < ft_strlen2d(mlx->map->mp_arrs)
			&& map_x >= 0 && map_x < ft_strlen(mlx->map->mp_arrs[0])
			&& mlx->map->mp_arrs[map_y][map_x] == '1')
		{
			hit->horz_x = next_x;
			hit->horz_y = next_y;
			hit->found_horz = 1;
			break ;
		}
		next_x += params.x_step;
		next_y += params.y_step;
	}
}
