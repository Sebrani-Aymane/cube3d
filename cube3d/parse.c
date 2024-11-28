/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:52 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/28 15:32:19 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int parse_map_name(char *av)
{
	int	len;

	len = ft_strlenn(av);

	if ((av[len - 1] != 'b' || av[len - 2] != 'u'
		|| av[len - 3] != 'c' || av[len - 4] != '.'))
		return (0);
	return (1);
}

int	get_texts_infos(char *line)
{
	char **str;

	str = ft_splitt(line, ' ');
	str[0] = ft_del_space(str[0]);
	if (!ft_strncmp(str[0], "NO", 2) || !ft_strncmp(str[0], "WE", 2)
		|| !ft_strncmp(str[0], "SO", 2) || !ft_strncmp(str[0], "EA", 2))
		return(free(str),1);
	return (0);
}

int get_colors_infos(char *line)
{
	char **str;
	
	str = ft_splitt(line, ' ');
	str[0] = ft_del_space(str[0]);
	if (!ft_strncmp(str[0], "F", 1) || !ft_strncmp(str[0], "C",1))
		return (free(str),1);
	return(0);
}

int	parse_map(char *str)
{
	int fd;
	char *line;
	int counter;
	t_map *map;

	map = malloc (sizeof(t_map));
	if (!map)
		return (write(2,"allocation error \n", 18), 1);
	counter = 0;
	fd = open(str,O_RDONLY);
	if (fd < 0)
		return (write(2,"couldn t open file\n", 19),1);
	while ((line = get_next_line(fd)))
	{
		if (!line)
			return (1);
		if (counter == 6)
		{
		//	if (get_map_infos(line) != NULL)
				return(1);
		}
		else if (get_texts_infos(line))
			if (map->map_texts = check_texts(line,map))
			counter++;
		else if (get_colors_infos(line))
		// {
		// 	if(map->map_clrs = check_colors(line,map))
 		counter++;
		// }
	}
	return(0);
}
