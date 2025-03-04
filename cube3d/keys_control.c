/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:45:59 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/04 01:20:15 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int is_valid_position(t_mlx *mlx, int new_x, int new_y)
{
    int map_x = new_x / mlx->range_ho_size;
    int map_y = new_y / mlx->range_ve_size;
    
    if (map_x < 0 || map_y < 0 || map_y >= ft_strlen2d(mlx->map->mp_arrs) || 
        map_x >= ft_strlen(mlx->map->mp_arrs[0]))
        return 0;
        
    return (mlx->map->mp_arrs[map_y][map_x] != '1');
}


void move_player(t_mlx *mlx, int forward)
{
	double move_angle = mlx->player_angle;
	double move_speed = mlx->move_speed;
	int new_x, new_y;

   if (!forward)
   {
        move_angle += M_PI;
        move_speed = move_speed * 0.8;
	}
    double dx = cos(move_angle) * move_speed;
    double dy = sin(move_angle) * move_speed;

    new_x = mlx->player_x + (int)dx;
    new_y = mlx->player_y + (int)dy;

   
    if (is_valid_position(mlx, new_x, mlx->player_y))
        mlx->player_x = new_x;
    if (is_valid_position(mlx, mlx->player_x, new_y))
        mlx->player_y = new_y;
    
    render_frame(mlx);
}

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

void rotate_player(t_mlx *mlx, int clockwise)
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

void    setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, close_wind, mlx);
	mlx_loop_hook(mlx->mlx, game_loop, mlx);
}