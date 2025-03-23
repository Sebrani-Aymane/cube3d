/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:41:31 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/23 10:13:10 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "mlx.h"

t_weapon_animation	*init_weapon_animation(t_mlx *mlx)
{
	t_weapon_animation	*weaponn;

	weaponn = c_malloc(sizeof(t_weapon_animation), 1);
	if (!weaponn)
		return (c_malloc(0, 0), NULL);
	weaponn->current_frame = 0;
	weaponn->frame_counter = 0;
	weaponn->frame_delay = 6;
	weaponn->is_attacking = 0;
	mlx->weapon = *weaponn;
	return (&mlx->weapon);
}

void	weapon_attack(t_weapon_animation *weapon)
{
	if (!weapon->is_attacking)
	{
		weapon->is_attacking = 1;
		weapon->current_frame = 0;
		weapon->frame_counter = 0;
	}
}

void	update_weapon_animation(t_weapon_animation *weapon)
{
	if (!weapon->is_attacking)
		return ;
	weapon->frame_counter++;
	if (weapon->frame_counter >= weapon->frame_delay)
	{
		weapon->frame_counter = 0;
		weapon->current_frame++;
		if (weapon->current_frame >= 4)
		{
			weapon->current_frame = 0;
			weapon->is_attacking = 0;
		}
	}
}

void	draw_weapon(t_mlx *mlx)
{
	t_texture	*current_texture;
	int			pos_x;
	int			pos_y;
	int			tex_x;
	int			tex_y;
	int			color;
	int			x;
	int			y;

	current_texture = &mlx->weapon.frames[mlx->weapon.current_frame];
	pos_x = (1200 / 2) - (current_texture->width / 2);
	pos_y = 720 - current_texture->height;
	y = 0;
	while (y < current_texture->height)
	{
		x = 0;
		while (x < current_texture->width)
		{
			tex_x = x;
			tex_y = y;
			color = get_texture_color(current_texture, tex_x, tex_y);
			if (color != 0x000000)
				my_mlx_pixel_put(mlx, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
	mlx_clear_window(mlx->mlx, mlx->win);
}

void	handle_weapon(t_mlx *mlx)
{
	mlx->weapon = *init_weapon_animation(mlx);
}