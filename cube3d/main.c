/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:43 by asebrani          #+#    #+#             */
/*   Updated: 2025/02/04 21:35:04 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
void set_textures(t_mlx *mlx)
{
	init_texture(mlx,&mlx->texs.north,"/Users/asebrani/Downloads/5a6d1b2bfc4f3b98639fa199c9c48d0d.xpm");
	init_texture(mlx,&mlx->texs.east,"/Users/asebrani/Downloads/ff9e205686e2676692e95a62732f654c.xpm");
	init_texture(mlx,&mlx->texs.south,"/Users/asebrani/Downloads/03ba785863e1857795cb846306370b71.xpm ");
	init_texture(mlx,&mlx->texs.west,"/Users/asebrani/Downloads/03aabd53ed7fb373e2736d68aabca2ed.xpm");
}
int	main(int ac, char **av)
{
	t_mlx *mlx;
	t_map *map;

	mlx = NULL;
	map = NULL;
	if (ac != 2 || !av[1])
		return (write(2,"Invalid arguments\n", 18), 0);
	if (!parse_map_name(av[1]))
		return(write(2, "invalid map name\n", 18), 0);
	if ( 0 != parse_map(av[1] ,&map))
		return(0);
	create_new_map(&map);
	parse_map_grid(map);
	map ->mp_arrs = replace_spaces_with_one(map->mp_arrs);
	mlx = malloc(sizeof(t_mlx));
    if (!mlx)
    {
        write(2, "Memory allocation failed\n", 24);
        return (0);
    }
	// printer(map ->mp_arrs);
	set_textures(mlx);
	map_tracing(map, mlx);
	return(printf("all good\n"), 1);
}