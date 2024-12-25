/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:43 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/12 05:25:23 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	map_tracing(map, mlx);
	return(printf("all good\n"), 1);
}