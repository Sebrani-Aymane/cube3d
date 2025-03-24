/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:09:31 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 00:25:22 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_double_lines(char *str)
{
	if (!str)
		return (write(2, "map error\n", 10), 1);
	if (str[ft_strlenn(str)] == '\n')
		return (1);
	while (*str)
	{
		if (*str == '\n' && *str == *(str + 1))
			return (write(2, "map error\n", 10), 1);
		str++;
	}
	return (0);
}

char	*collect_map_lines(int fd, char *line)
{
	char	*join;
	char	*temp;

	join = ft_strdup("");
	if (!join)
		return (NULL);
	if (*line == '1' || *line == '0')
		temp = line;
	else
		temp = get_next_line(fd);
	if (!temp)
	{
		write(2, "Error map!\n", 12);
		return (NULL);
	}
	while (temp)
	{
		join = ft_strjoin(join, temp);
		if (!join)
			return (NULL);
		temp = get_next_line(fd);
	}
	return (join);
}

int	validate_and_process_map(char *joined_map, t_map *map)
{
	char	**map_grid;

	if (check_double_lines(joined_map))
		return (0);
	map_grid = ft_splitt(joined_map, '\n');
	if (!map_grid)
		return (0);
	map->mp_arrs = map_grid;
	return (1);
}

int	parse_map_strct(t_map *map, int fd, char *line)
{
	char	*joined_map;

	if (!line || !*line || (*line != ' ' && *line != '1' && *line != '\n'))
	{

		write(2, "Error map!\n", 12);
		close(fd);
		return (0);
	}
	joined_map = collect_map_lines(fd, line);
	if (!joined_map)
	{
		close(fd);
		return (0);
	}
	if (!validate_and_process_map(joined_map, map))
	{
		close(fd);
		return (0);
	}
	return (1);
}

int	parse_map_grid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	if (!check_set_chars(map->mp_arrs[0], '1'))
		return (write(2, "0 is near a space\n", 18), 0);
	while (map->mp_arrs[i])
	{
		j = 0;
		while (map->mp_arrs[i][j])
		{
			if (map->mp_arrs[i][j] == '0')
				if (!check_for_surrounds(i, j, map->mp_arrs))
					return (0);
			j++;
		}
		i++;
	}
	if (!check_set_chars(map->mp_arrs[i - 1], '1'))
		return (write(2, "0 is near a space\n", 18), 0);
	return (1);
}
