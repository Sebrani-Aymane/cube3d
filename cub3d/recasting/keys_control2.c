/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:20:50 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/24 04:08:47 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	compute_movement(t_mlx *mlx, int forward, int *new_x, int *new_y)
{
	double	move_angle;
	double	move_speed;
	double	direction;
	double	dx;
	double	dy;

	move_angle = mlx->player_angle;
	move_speed = mlx->move_speed;
	direction = 0;
	if (!forward)
	{
		direction = M_PI;
		move_speed *= 0.8;
	}
	dx = cos(move_angle + direction) * move_speed;
	dy = sin(move_angle + direction) * move_speed;
	*new_x = mlx->player_x + (int)dx;
	*new_y = mlx->player_y + (int)dy;
}

void	move_player(t_mlx *mlx, int forward)
{
	int	new_x;
	int	new_y;

	compute_movement(mlx, forward, &new_x, &new_y);
	update_position(mlx, new_x, new_y);
	render_frame(mlx);
}

void	compute_strafe_movement(t_mlx *mlx, int right, int *new_x, int *new_y)
{
	double	strafe_angle;
	double	move_speed;
	double	dx;
	double	dy;

	strafe_angle = mlx->player_angle + (M_PI / 2);
	move_speed = mlx->move_speed * 0.8;
	if (!right)
		strafe_angle += M_PI;
	dx = cos(strafe_angle) * move_speed;
	dy = sin(strafe_angle) * move_speed;
	*new_x = mlx->player_x + (int)dx;
	*new_y = mlx->player_y + (int)dy;
}

void	strafe_player(t_mlx *mlx, int right)
{
	int	new_x;
	int	new_y;

	compute_strafe_movement(mlx, right, &new_x, &new_y);
	if (is_valid_position(mlx, new_x, mlx->player_y))
		mlx->player_x = new_x;
	if (is_valid_position(mlx, mlx->player_x, new_y))
		mlx->player_y = new_y;
	render_frame(mlx);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	i;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return (0);
	if (x > i)
		mlx->player_angle += mlx->rotation_speed;
	else if (x < i)
		mlx->player_angle -= mlx->rotation_speed;
	i = x;
	if (mlx->player_angle < 0)
		mlx->player_angle += 2 * M_PI;
	return (0);
}
