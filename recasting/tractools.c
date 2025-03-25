/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tractools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:41:23 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/02/16 08:22:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_strlen2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
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

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_lentgh + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
