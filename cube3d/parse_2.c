/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:33:58 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/02 05:05:23 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <errno.h>
void free_split_array(char **arr)
{
	int i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


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
		free_split_array(str);
		return (NULL);
	}
	free(line);
	if (!is_valid_file(str[1]))
	{
		write(2, "Error: Cannot access texture file\n", 35);
		free_split_array(str);
		return (NULL);
	}
	if (is_duplicate_direction(str[0], map))
	{
		free_split_array(str);
		return (NULL);
	}
	if (ft_strcmp(str[0], "NO") == 0)
		map->no_texts = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "SO") == 0)
		map->so_texts = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "WE") == 0)
		map->we_texts = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "EA") == 0)
		map->ea_texts = ft_strdup(str[1]);
	free_split_array(str);
	return (map);
}

