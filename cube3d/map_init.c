/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:54:45 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/30 11:51:17 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void map_init(t_map *map)
{
    map->ceiling_clr[0] = 0;
    map->ceiling_clr[1] = 0;
    map->ceiling_clr[2] = 0;
    map->floor_clr[0] = 0;
    map->floor_clr[1] = 0;
    map->floor_clr[2] = 0;
    map->no_texts = NULL;
    map->so_texts = NULL;
    map->we_texts = NULL;
    map->ea_texts = NULL;
    return;
}
int check_texture_completeness(t_map *map)
{
    int direction_count = 0;

    if (map->no_texts) direction_count++;
    if (map->so_texts) direction_count++;
    if (map->we_texts) direction_count++;
    if (map->ea_texts) direction_count++;
    if (direction_count != 4) {
        write(2, "Error: Missing or incomplete texture directions\n", 47);
        return 0;
    }

    return 1;
}

int is_duplicate_direction(char *direction, t_map *map)
{
    if (!direction)
        return 1;

    if (ft_strcmp(direction, "NO") == 0 && map->no_texts)
    {
        write(2, "Error: Duplicate NO texture\n", 27);
        return 1;
    }
    if (ft_strcmp(direction, "SO") == 0 && map->so_texts)
    {
        write(2, "Error: Duplicate SO texture\n", 27);
        return 1;
    }
    if (ft_strcmp(direction, "WE") == 0 && map->we_texts)
    {
        write(2, "Error: Duplicate WE texture\n", 27);
        return 1;
    }
    if (ft_strcmp(direction, "EA") == 0 && map->ea_texts)
    {
        write(2, "Error: Duplicate EA texture\n", 27);
        return 1;
    }

    return 0;
}