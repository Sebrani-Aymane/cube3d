/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:54:45 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 14:37:21 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_map	*map_init(void)
{
	t_map	*map;

	map = c_malloc(sizeof(t_map), 1);
	if (!map)
		return (write(2, "Error: Memory allocation failed\n", 33), NULL);
	map->ceiling_clr[0] = -1;
	map->ceiling_clr[1] = -1;
	map->ceiling_clr[2] = -1;
	map->floor_clr[0] = -1;
	map->floor_clr[1] = -1;
	map->floor_clr[2] = -1;
	map->no_texts = NULL;
	map->so_texts = NULL;
	map->we_texts = NULL;
	map->ea_texts = NULL;
	map->mp_arrs = NULL;
	return (map);
}

int	check_texture_completeness(t_map *map)
{
	int	direction_count;
	int	color_count;

	direction_count = 0;
	color_count = 0;
	if (map->no_texts && map->so_texts && map->we_texts && map->ea_texts)
		direction_count = 4;
	if (map->floor_clr[0] != -1 && map->floor_clr[1] != -1
		&& map->floor_clr[2] != -1)
		color_count++;
	if (map->ceiling_clr[0] != -1
		&& map->ceiling_clr[1] != -1
		&& map->ceiling_clr[2] != -1)
		color_count++;
	if (direction_count != 4 || color_count != 2)
		return (write(2,
				"Error: Missing or incomplete texture directions\n", 47), 0);
	return (1);
}

int	is_duplicate_direction(char *direction, t_map *map)
{
	if (!direction)
		return (1);
	if (ft_strcmp(direction, "NO") == 0 && map->no_texts)
		return (write(2, "Error: Duplicate NO texture\n", 27), 1);
	if (ft_strcmp(direction, "SO") == 0 && map->so_texts)
		return (write(2, "Error: Duplicate SO texture\n", 27), 1);
	if (ft_strcmp(direction, "WE") == 0 && map->we_texts)
		return (write(2, "Error: Duplicate WE texture\n", 27), 1);
	if (ft_strcmp(direction, "EA") == 0 && map->ea_texts)
		return (write(2, "Error: Duplicate EA texture\n", 27), 1);
	return (0);
}

int	check_set_chars(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
