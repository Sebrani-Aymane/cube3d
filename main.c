/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:43 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 03:50:44 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_colos(t_map *map, t_mlx *mlx)
{
	mlx->floor_color = map->floor_clr[0] << 16
		| map->floor_clr[1] << 8 | map->floor_clr[2];
	mlx->ceiling_color = map->ceiling_clr[0] << 16
		| map->ceiling_clr[1] << 8 | map->ceiling_clr[2];
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	t_map	*map;

	mlx = NULL;
	map = NULL;
	if (ac != 2 || !av[1])
		return (write(2, "Invalid arguments\n", 18), 0);
	if (!parse_map_name(av[1]))
		return (write(2, "invalid map name\n", 18), 0);
	if (0 != parse_map(av[1], &map))
		return (0);
	create_new_map(&map);
	if (!parse_map_grid(map))
		return (0);
	map ->mp_arrs = replace_spaces_with_one(map->mp_arrs);
	mlx = c_malloc(sizeof(t_mlx), 1);
	if (!mlx)
		return (write(2, "Memory allocation failed\n", 24), 0);
	set_colos(map, mlx);
	handle_weapon(mlx);
	set_textures(map, mlx);
	map_tracing(map, mlx);
	c_malloc(0, 0);
	return (printf("all good\n"), 1);
}
