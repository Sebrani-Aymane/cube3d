/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-21 03:17:02 by kaafkhar          #+#    #+#             */
/*   Updated: 2024-12-21 03:17:02 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_frame(t_mlx *mlx)
{
    int total_bytes;
    int i;

    if (!mlx || !mlx->addr || !mlx->map)
        return;
    total_bytes = WIDTH * HEIGHT * (mlx->bits_per_pixel / 8);
    i = 0;
    while (i < total_bytes)
    {
        mlx->addr[i] = 0;
        i++;
    }
    draw2d(mlx->map, mlx);
    cast_rays(mlx);
    draw_walls(mlx);
    my_mlx_pixel_put(mlx, mlx->player_x, mlx->player_y, 0xff0000);
    // draw_grid(mlx, mlx->range_ho_size, mlx->range_ve_size);
    // draw_pov(mlx->map, mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void map_tracing(t_map *map, t_mlx *mlx)
{
	initialize_mlx(mlx);
	mlx->keys = (t_keys){0, 0, 0, 0, 0, 0};
	initialize_map_settings(map, mlx);
	render_frame(mlx);
	setup_hooks(mlx);
	mlx_loop(mlx->mlx);
}