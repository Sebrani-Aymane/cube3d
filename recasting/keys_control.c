/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:48:30 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/22 03:29:05 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	rotate_player(t_mlx *mlx, int clockwise)
{
	if (clockwise)
		mlx->player_angle += mlx->rotation_speed;
	else
		mlx->player_angle -= mlx->rotation_speed;
	mlx->player_angle = fmod(mlx->player_angle, 2 * M_PI);
	if (mlx->player_angle < 0)
		mlx->player_angle += 2 * M_PI;
	render_frame(mlx);
}

int	game_loop(t_mlx *mlx)
{
	if (mlx->keys.w_pressed)
		move_player(mlx, 1);
	if (mlx->keys.s_pressed)
		move_player(mlx, 0);
	if (mlx->keys.left_pressed)
		rotate_player(mlx, 0);
	if (mlx->keys.right_pressed)
		rotate_player(mlx, 1);
	if (mlx->keys.a_pressed)
		strafe_player(mlx, 0);
	if (mlx->keys.d_pressed)
		strafe_player(mlx, 1);
	if (mlx->keys.attack)
		mlx->weapon.is_attacking = 1;
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		mlx->keys.w_pressed = 0;
	else if (keycode == 1)
		mlx->keys.s_pressed = 0;
	else if (keycode == 0)
		mlx->keys.a_pressed = 0;
	else if (keycode == 2)
		mlx->keys.d_pressed = 0;
	else if (keycode == 123)
		mlx->keys.left_pressed = 0;
	else if (keycode == 124)
		mlx->keys.right_pressed = 0;
	else if (keycode == 72)
		mlx->keys.attack = 0;
	return (0);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if (keycode == 13)
		mlx->keys.w_pressed = 1;
	else if (keycode == 1)
		mlx->keys.s_pressed = 1;
	else if (keycode == 0)
		mlx->keys.a_pressed = 1;
	else if (keycode == 2)
		mlx->keys.d_pressed = 1;
	else if (keycode == 123)
		mlx->keys.left_pressed = 1;
	else if (keycode == 124)
		mlx->keys.right_pressed = 1;
	else if (keycode == 72)
		mlx->keys.attack=1;
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, close_wind, mlx);
	mlx_loop_hook(mlx->mlx, game_loop, mlx);
}
