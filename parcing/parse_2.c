/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:33:58 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/19 05:44:22 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	validate_texture_input(char *line, char ***str)
{
	int	arr_len;
	int	i;

	if (!line)
	{
		write(2, "Error: Invalid input to check_texts\n", 36);
		return (0);
	}
	*str = ft_splitt(line, ' ');
	if (!*str)
	{
		write(2, "Error: Failed to split line\n", 28);
		return (0);
	}
	arr_len = 0;
	i = 0;
	while ((*str)[i++])
		arr_len++;
	if (arr_len != 2)
	{
		write(2, "Error: Invalid texture definition\n", 34);
		return (0);
	}
	return (1);
}

int	assign_texture_path(char **str, t_map *map)
{
	char	*trimmed;

	if (!is_valid_file(str[1]))
	{
		write(2, "Error: Cannot access/locate texture file\n", 41);
		return (0);
	}
	if (is_duplicate_direction(str[0], map))
		return (0);
	trimmed = ft_strtrim(str[1], "\n");
	if (ft_strcmp(str[0], "NO") == 0)
		map->no_texts = ft_strdup(trimmed);
	else if (ft_strcmp(str[0], "SO") == 0)
		map->so_texts = ft_strdup(trimmed);
	else if (ft_strcmp(str[0], "WE") == 0)
		map->we_texts = ft_strdup(trimmed);
	else if (ft_strcmp(str[0], "EA") == 0)
		map->ea_texts = ft_strdup(trimmed);
	return (1);
}

t_map	*check_texts(char *line, t_map *map)
{
	char	**str;

	if (!map)
	{
		write(2, "Error: Invalid input to check_texts\n", 36);
		return (NULL);
	}
	if (!validate_texture_input(line, &str))
		return (NULL);
	if (!assign_texture_path(str, map))
		return (NULL);
	return (map);
}
