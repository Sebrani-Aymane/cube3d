/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_sauce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 05:22:35 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/11 02:27:18 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	find_max_line_length(char **map)
{
	int	max_len;
	int	current_len;
	int	i; 

	max_len = 0;
	i = 0;
	while (map[i])
	{
	current_len = ft_strlen(map[i]);
	if (current_len > max_len)
	max_len = current_len;
	i++;
	}
	return (max_len);
}

char	**replace_spaces_with_one(char **map)
{
   int	rows;
   int	max_len;
   int	current_len;
   int	i;
   int	j;
   char	**new_map;

	rows = count_map_rows(map);
	max_len = find_max_line_length(map);
	new_map = c_malloc((rows + 1) * sizeof(char *), 1);
	if (!new_map)
		return (NULL);
   i = 0;
   while (i < rows)
   {
		current_len = ft_strlen(map[i]);

	   new_map[i] = c_malloc(max_len + 1,1);
	   if (!new_map[i])
	   {	c_malloc(0,0);
		   return (NULL);
	   }

	   j = 0;
	   while (j < max_len)
	   {
		   new_map[i][j] = '1';
		   j++;
	   }
	   new_map[i][max_len] = '\0';

	   j = 0;
	   while (j < current_len)
	   {
		   if (map[i][j] == ' ' && 
			   (i == 0 || i == rows - 1 || j == 0 || j == current_len - 1))
		   {
			   j++;
			   continue;
		   }

		   if (map[i][j] == ' ')
			   new_map[i][j] = '1';
		   else
			   new_map[i][j] = map[i][j];
		   j++;
	   }
	   i++;
   }

   new_map[rows] = NULL;
   return (new_map);
}