/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 04:54:51 by asebrani          #+#    #+#             */
/*   Updated: 2025/02/17 04:11:57 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int find_player(t_map *map)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while(map->mp_arrs[i])
	{
		j = 0;
		while(map->mp_arrs[i][j])
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

void printer(char **str)
{
	int i;
	i = 0;

	while (str[i])
	{
		printf("%s\n",str[i]);
		i++;
	}
}

int validate_map(t_map *map)
{
	int i;
	int j;
	char curr;

	i = 0;
	while (map->mp_arrs[i])
	{
		j = 0;
		while (map->mp_arrs[i][j])
		{
			curr = map->mp_arrs[i][j];
			if (curr != '0' && curr != '\n' &&
				curr != '1' && curr != ' ')
			{
				if (curr != 'E' && curr != 'W' &&        
					curr != 'S' && curr != 'N')
					return (write(2, "invalid char in map\n", 20),1);
				map->x_player_pos = j;
				map->y_player_pos = i;
				map->start_direction = curr;
			}
			j++;
		}
		i++;
	}

	return (0);
}

int count_map_rows(char **map)
{
    int rows;

    if (!map)
        return (0);

    rows = 0;
    while (map[rows] != NULL)
        rows++;

    return (rows);
}
int check_for_surrounds(int i, int j, char **map)
{
    int map_rows;
    int row_len;
    if (!map || !map[i])
        return (1);
    map_rows = count_map_rows(map);
    row_len = ft_strlen(map[i]);
    if (j > 0 && j + 1 < row_len)
    {
        if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
            return (write(2, "0 is near a space\n", 18), 0);
    }
    if (i > 0 && i + 1 < map_rows)
    {
        if (j < ft_strlen(map[i-1]) && map[i-1][j] == ' ')
            return (write(2, "0 is near a space\n", 18), 0);
        if (j < ft_strlen(map[i+1]) && map[i+1][j] == ' ')
            return (write(2, "0 is near a space\n", 18), 0);
    }
    return (1);
}
void create_new_map(t_map **map)
{
	char *temp;
	int i;
	int len;
	
	if (!map || !*map)
		return;
	
	i = 0;
	while ((*map)->mp_arrs[i])
	{
		len = ft_strlen((*map)->mp_arrs[i]);
	
		temp = malloc(len + 3);
		if (!temp)
			return;
	    temp[0] = ' ';
		ft_strlcpy(temp + 1, (*map)->mp_arrs[i], len + 1);
		temp[len + 1] = ' ';
		temp[len + 2] = '\0';
		free((*map)->mp_arrs[i]);
		(*map)->mp_arrs[i] = temp;
		i++;
	}
}