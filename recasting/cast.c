/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:13:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/11 02:26:18 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	draw_wall(t_mlx *mlx, int strip_id)
{
	int			color;
	int			tex_y;
	double		tex_x;
	t_draw_data	d;
	t_texture	*texture;

	prepare_wall_texture(mlx, strip_id, &texture, &tex_x);
	d.wall_height = (mlx->range_ve_size * HEIGHT)
		/ mlx->rays[strip_id].distance;
	d.wall_top = (HEIGHT / 2) - (d.wall_height / 2);
	d.wall_bottom = (HEIGHT / 2) + (d.wall_height / 2);
	d.tex_offset = (double)texture->height / d.wall_height;
	//sma
	d.y = 0;
	while (d.y < d.wall_top)
	{
		my_mlx_pixel_put(mlx, strip_id, d.y, mlx->ceiling_color);
		d.y++;
	}
	//hwiyet
	while (d.y < d.wall_bottom)
	{
		tex_y = (d.y - d.wall_top) * d.tex_offset;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(mlx, strip_id, d.y, color);
		d.y++;
	}
	//l ard
	while (d.y < HEIGHT)
	{
		my_mlx_pixel_put(mlx, strip_id, d.y, mlx->floor_color);
		d.y++;
	}
}

void	initialize_ray(t_rays *ray, float ray_angle)
{
	ray->facing_down = ray_angle > 0 && ray_angle < M_PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2;
	ray->facing_left = !ray->facing_right;
}

float	normal_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	cast_rays(t_mlx *mlx)
{
	int						strip_id;
	float					ray_angle;
	t_player				player;
	t_hit_points			hit;
	t_rays					*ray;

	player.x = mlx->player_x;
	player.y = mlx->player_y;
	player.angle = mlx->player_angle;
	strip_id = 0;
	ray_angle = mlx->player_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		ray_angle = normal_angle(ray_angle);
		ray = &mlx->rays[strip_id];
		initialize_ray(ray, ray_angle);
		hit = (t_hit_points){0};
		find_horizontal_hit(mlx, ray, ray_angle, &hit);
		find_vertical_hit(mlx, ray, ray_angle, &hit);
		choose_closest_hit(ray, &hit, &player);
		finalize_ray(ray, ray_angle, mlx->player_angle);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		draw_wall(mlx, strip_id);
		strip_id++;
	}
}
