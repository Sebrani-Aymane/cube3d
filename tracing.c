/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-19 19:02:12 by kaafkhar          #+#    #+#             */
/*   Updated: 2024-12-19 19:02:12 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    map_tracing(t_map *map, t_mlx *mlx)
{
    (void)map;
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx, 1920, 1080, "cub3d");
    mlx_loop(mlx->mlx);
}
