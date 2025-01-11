/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 03:45:59 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-11 03:45:59 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void strafe_player(t_mlx *mlx, int right)
{
	double strafe_angle;
	double move_speed;
	double dx;
	double dy;
	int new_x;
	int new_y;

	strafe_angle = mlx->player_angle + (M_PI / 2);
	move_speed = mlx->move_speed * 0.8;
	if (!right)
		strafe_angle += M_PI;
	dx = cos(strafe_angle) * move_speed;
	dy = sin(strafe_angle) * move_speed;
	new_x = mlx->player_x + (int)dx;
	new_y = mlx->player_y + (int)dy;
	if (is_valid_position(mlx, new_x, mlx->player_y))
		mlx->player_x = new_x;
	if (is_valid_position(mlx, mlx->player_x, new_y))
		mlx->player_y = new_y;
	render_frame(mlx);
}


int key_press(int keycode, t_mlx *mlx)
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
    return (0);
}

int key_release(int keycode, t_mlx *mlx)
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
    return (0);
}

int game_loop(t_mlx *mlx)
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
	return (0);
}