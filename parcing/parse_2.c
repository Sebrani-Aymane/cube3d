/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:33:58 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/11 02:36:18 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <errno.h>
t_map *check_texts(char *line, t_map *map)
{
	char **str;
	int i = 0;
	int arr_len;

	if (!line || !map)
	{
		write(2, "Error: Invalid input to check_texts\n", 36);
		return (NULL);
	}
	
	str = ft_splitt(line, ' ');
	if (!str)
	{
		write(2, "Error: Failed to split line\n", 28);
		return (NULL);
	}
	
	arr_len = 0;
	while (str[i++])
		arr_len++;
	if (arr_len != 2)
	{
		write(2, "Error: Invalid texture definition\n", 34);
		return (NULL);
	}
	// if (!is_valid_file(str[1]))
	// {
	// 	write(2, "Error: Cannot access/locate texture file\n", 41);
	// 	return (NULL);
	// }
	if (is_duplicate_direction(str[0], map))
		return (NULL);
	if (ft_strcmp(str[0], "NO") == 0)
		map->no_texts = ft_strdup(ft_strtrim(str[1],"\n"));
	else if (ft_strcmp(str[0], "SO") == 0)
		map->so_texts = ft_strdup(ft_strtrim(str[1],"\n"));
	else if (ft_strcmp(str[0], "WE") == 0)
		map->we_texts = ft_strdup(ft_strtrim(str[1],"\n"));
	else if (ft_strcmp(str[0], "EA") == 0)
		map->ea_texts = ft_strdup(ft_strtrim(str[1],"\n"));
//	free_split_array(str);
	return (map);
}


