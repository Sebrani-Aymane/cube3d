/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tractools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-23 17:41:23 by kaafkhar          #+#    #+#             */
/*   Updated: 2024-12-23 17:41:23 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlen2d(char **str)
{
	int i;

	i = 0;
	while(str[i] != NULL)
		i++;
	return(i);
}

int handle_keys(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return 0;

}

int	close_wind(t_mlx *mlx)
{
	
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_lentgh + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}