/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:09:31 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/12 05:30:27 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_double_lines(char *str)
{
	if (!str)
		return (write(2,"map error\n", 10), 1);
	if (str[ft_strlenn(str)] == '\n')
		return (1);
	while (*str)
	{
		if (*str == '\n' && *str == *(str + 1))
			return (write(2,"map error\n", 10),1);
		str++;
	}
	return (0);
}

int parse_map_strct(t_map *map, int fd,char *line)
{
    char **map_grid;
    int i;
    int j;
    char	*temp;
	char	*join;
    i = j = 0;
	temp = NULL;
	join = ft_strdup("");
	if (*line == '1' || *line == '0')
		temp = line;
	else 
		temp = get_next_line(fd);
	if (!temp)
		return(write(2, "Error map!\n", 12),close(fd) ,0);
	while (temp)
	{
		join = ft_strjoin(join, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	if (check_double_lines(join))
		return (free(join) , 0);
	map_grid = ft_splitt(join, '\n');
	free(join);
	map->mp_arrs = map_grid;
	return 1;
}

int parse_map_grid(t_map *map)
{
	int i;
	int j;
	i = 0;
	check_set_chars(map->mp_arrs[0], '1');

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
	return(1);
}