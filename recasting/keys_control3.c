/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-21 03:42:39 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-03-21 03:42:39 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_wall(t_mlx *mlx, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->range_ho_size;
	map_y = y / mlx->range_ve_size;
	if (map_x < 0 || map_y < 0 || map_y >= ft_strlen2d(mlx->map->mp_arrs)
		|| map_x >= ft_strlen(mlx->map->mp_arrs[0]))
		return (1);
	return (mlx->map->mp_arrs[map_y][map_x] == '1');
}

int	is_valid_position(t_mlx *mlx, int new_x, int new_y)
{
	int	buffer;
	int	check_points[4][2];
	int	i;

	buffer = 10;
	if (is_wall(mlx, new_x, new_y))
		return (0);
	check_points[0][0] = new_x + buffer;
	check_points[0][1] = new_y;
	check_points[1][0] = new_x - buffer;
	check_points[1][1] = new_y;
	check_points[2][0] = new_x;
	check_points[2][1] = new_y + buffer;
	check_points[3][0] = new_x;
	check_points[3][1] = new_y - buffer;
	i = 0;
	while (i < 4)
	{
		if (is_wall(mlx, check_points[i][0], check_points[i][1]))
			return (0);
		i++;
	}
	return (1);
}

int	is_clear_direction(t_mlx *mlx, int new_x, int new_y, double direction)
{
	int	look_ahead_distance;
	int	check_x;
	int	check_y;

	look_ahead_distance = 10;
	check_x = new_x + (int)(cos(mlx->player_angle + direction)
			* look_ahead_distance);
	check_y = new_y + (int)(sin(mlx->player_angle + direction)
			* look_ahead_distance);
	if (mlx->map->mp_arrs[check_y / mlx->range_ve_size]
		[check_x / mlx->range_ho_size] == '1')
		return (0);
	return (1);
}

void	update_position(t_mlx *mlx, int new_x, int new_y)
{
	if (is_clear_direction(mlx, new_x, mlx->player_y, 0))
	{
		if (is_valid_position(mlx, new_x, mlx->player_y))
			mlx->player_x = new_x;
	}
	if (is_clear_direction(mlx, mlx->player_x, new_y, 0))
	{
		if (is_valid_position(mlx, mlx->player_x, new_y))
			mlx->player_y = new_y;
	}
}

void	prepare_wall_texture(t_mlx *mlx, int strip_id, t_texture **texture,
							double *tex_x)
{
	if (mlx->rays[strip_id].hit_ver)
	{
		*tex_x = fmod(mlx->rays[strip_id].wallhity, 64);
		if (mlx->rays[strip_id].facing_left)
			*texture = &mlx->texs.west;
		else
			*texture = &mlx->texs.east;
	}
	else
	{
		*tex_x = fmod(mlx->rays[strip_id].wallhitx, 64);
		if (mlx->rays[strip_id].facing_down)
			*texture = &mlx->texs.south;
		else
			*texture = &mlx->texs.north;
	}
	*tex_x = (*tex_x * (*texture)->width) / 64;
	if (mlx->rays[strip_id].hit_ver && mlx->rays[strip_id].facing_left)
		*tex_x = (*texture)->width - *tex_x;
	if (!mlx->rays[strip_id].hit_ver && mlx->rays[strip_id].facing_down)
		*tex_x = (*texture)->width - *tex_x;
}
