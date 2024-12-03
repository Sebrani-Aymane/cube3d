/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:52 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/03 02:31:01 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_map_name(char *av)
{
	int	len;

	len = ft_strlenn(av);
	if (len < 4 || av[len - 1] != 'b' || av[len - 2] != 'u'
		|| av[len - 3] != 'c' || av[len - 4] != '.')
		return (0);
	return (1);
}

int	get_texts_infos(char *line)
{
	char	**str;
	int		result;

	str = ft_splitt(line, ' ');
	if (!str)
		return (0);
	str[0] = ft_del_space(str[0]);
	result = (!ft_strncmp(str[0], "NO", 2) || !ft_strncmp(str[0], "WE", 2)
			|| !ft_strncmp(str[0], "SO", 2) || !ft_strncmp(str[0], "EA", 2));
	free(str);
	return (result);
}

int	get_colors_infos(char *line)
{
	char	**str;
	int		result;

	str = ft_splitt(line, ' ');
	if (!str)
		return (0);
	str[0] = ft_del_space(str[0]);
	result = (!ft_strncmp(str[0], "F", 1) || !ft_strncmp(str[0], "C", 1));
	free(str);
	return (result);
}

void	free_map(t_map *map)
{
	if (map)
		free(map);
}

int parse_map(char *str)
{
	int     fd;
	char    *line;
	int     counter_clr;
	int     counter_texts;
	t_map   *map;
	char *after;

	map = malloc(sizeof(t_map));
	if (!map)
		return (write(2, "Error: Memory allocation failed\n", 33), 1);
	map_init(map);
	counter_clr=counter_texts = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (free_map(map), write(2, "Error: Couldn't open file\n", 27), 1);
		map->fd = fd;
	while ((line = get_next_line(fd)))
	{
		after = ft_strtrim(line," \t");
		if (!after || *after == '\n')
			continue;
		free(line);
		if ((*after == '1' || *after =='0') || (counter_clr == 2 && counter_texts == 4) )
		{
			//free(line);
			break;
		}
		if (get_texts_infos(after))
		{
			map = check_texts(after, map);
			if (!map)
			{
				//free(after);
				return (free_map(map), close(fd), 1);
			}
			counter_texts++;
		}
		else if (parse_color_line(after,map))
		{
			counter_clr++;
		}

	}
	int flag;
	flag = 0;
	if (!check_texture_completeness(map))
	{
		free(after);
			return (free_map(map), close(fd), 1);
	}
	else
	{
		if (*after == '1')
			flag = 1;
		//map->map_arrays = parse_map_strct(map,fd,after,flag);
	}
	return (0);
}
