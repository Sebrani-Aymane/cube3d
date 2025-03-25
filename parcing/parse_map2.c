/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 04:54:51 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 06:57:06 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->mp_arrs[i])
	{
		j = 0;
		while (map->mp_arrs[i][j])
		{
			if ((map->mp_arrs[i][j] == 'N' || map->mp_arrs[i][j] == 'S' ||
				map->mp_arrs[i][j] == 'W' || map->mp_arrs[i][j] == 'E'))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	validate_map(t_map *map)
{
	int		i;
	int		j;
	char	curr;

	i = -1;
	while (map->mp_arrs[++i])
	{
		j = -1;
		while (map->mp_arrs[i][++j])
		{
			curr = map->mp_arrs[i][j];
			if (curr != '0' && curr != '\n'
				&& curr != '1' && curr != ' ')
			{
				if (curr != 'E' && curr != 'W' && curr != 'S' && curr != 'N')
					return (write(2, "invalid char in map\n", 20), 1);
				if (!check_for_surrounds(i, j, map->mp_arrs))
					return (write(2, "Player is near a space\n", 23), 1);
				map->x_player_pos = j;
				map->y_player_pos = i;
				map->start_direction = curr;
			}
		}
	}
	return (0);
}

int	count_map_rows(char **map)
{
	int	rows;

	if (!map)
		return (0);
	rows = 0;
	while (map[rows] != NULL)
		rows++;
	return (rows);
}

int	check_for_surrounds(int i, int j, char **map)
{
	int	map_rows;
	int	row_len;

	if (!map || !map[i])
		return (1);
	map_rows = count_map_rows(map);
	row_len = ft_strlen(map[i]);
	if (j > 0 && j + 1 < row_len)
	{
		if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
			|| (!map[i][j - 1] || !map[i][j + 1]))
			return (write(2, "Error: player is near a space\n", 30), 0);
	}
	if (i > 0 && i + 1 < map_rows)
	{
		if (j >= ft_strlen(map[i - 1])
			|| (map[i - 1][j] && map[i - 1][j] == ' '))
			return (write(2, "Error: player is near a space\n", 30), 0);
		if (j >= ft_strlen(map[i + 1])
			|| (map[i + 1][j] && map[i + 1][j] == ' '))
			return (write(2, "Error: player is near a space\n", 30), 0);
	}
	return (1);
}

void	create_new_map(t_map **map)
{
	char	*temp;
	int		i;
	int		len;

	if (!map || !*map)
		return ;
	i = 0;
	while ((*map)->mp_arrs[i])
	{
		len = ft_strlen((*map)->mp_arrs[i]);
		temp = c_malloc((len + 3), 1);
		if (!temp)
			return ;
		temp[0] = ' ';
		ft_strlcpy(temp + 1, (*map)->mp_arrs[i], len + 1);
		temp[len + 1] = ' ';
		temp[len + 2] = '\0';
		(*map)->mp_arrs[i] = temp;
		i++;
	}
}
