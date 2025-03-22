/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 03:17:02 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/22 07:05:37 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	render_frame(t_mlx *mlx)
{
	int	total_bytes;
	int	i;

	if (!mlx || !mlx->addr || !mlx->map)
		return ;
	total_bytes = WIDTH * HEIGHT * (mlx->bits_per_pixel / 8);
	i = 0;
	while (i < total_bytes)
	{
		mlx->addr[i] = 0;
		i++;
	}
	place_player(mlx->map, mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	
}

void	map_tracing(t_map *map, t_mlx *mlx)
{
	initialize_mlx(mlx);
	mlx->keys = (t_keys){0, 0, 0, 0, 0, 0};
	initialize_map_settings(map, mlx);
	setup_hooks(mlx);
	render_frame(mlx);
	mlx_loop(mlx->mlx);
}
