/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 04:54:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/10 15:37:02 by asebrani         ###   ########.fr       */
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
            if (map->mp_arrs[i][j] == 'N' || map->mp_arrs[i][j] == 'S' || 
                map->mp_arrs[i][j] == 'W' || map->mp_arrs[i][j] == 'E')
                count++;
			j++;
		}
		i++;
	}
    if (count != 1)
        return (0);
    return (1);
}

static void printer(char **str)
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
    printer(map->mp_arrs);
    return (0);
}

int check_for_surrounds(int i,int j, char **map)
{
    char curr;
    curr = map[i][j];
    if(map[i][j + 1] && map[i][j - 1])
    {
        if(map[i][j + 1]  == ' ' || map[i][j - 1] == ' ')
            return (write(2,"0 is near a space\n", 18), 0);
    }
    if (map[i + 1][j] && map[i - 1][j])
    {
        if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
        return (write(2,"0 is near a space\n", 18), 0);
    }
    return (1);
        
}