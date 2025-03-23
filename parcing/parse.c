/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:52 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/23 10:01:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	handle_map_file_open(char *str, t_map **map, int *fd)
{
	*map = map_init();
	if (!*map)
		return (c_malloc(0, 0), 1);
	*fd = open(str, O_RDONLY);
	if (*fd < 0)
		return (c_malloc(0, 0), write(2, "Error: Couldn't open file\n", 27), 1);
	(*map)->fd = *fd;
	return (0);
}

int	process_map_line(char *line, t_map **map,
	int *counter_clr, int *counter_texts)
{
	char	*after;

	after = ft_strtrim(line, " \t");
	if (!after || *after == '\n')
		return (0);
	if ((*after == '1' || *after == '0')
		|| (*counter_clr == 2 && *counter_texts == 4))
		return (1);
	if (get_texts_infos(after))
	{
		*map = check_texts(after, *map);
		if (!*map)
			return (2);
		(*counter_texts)++;
	}
	else if (parse_color_line(after, *map))
		(*counter_clr)++;
	return (0);
}

int	read_map_configuration(t_map **map, int fd, char **line)
{
	int		counter_clr;
	int		counter_texts;
	int		result;

	counter_clr = 0;
	counter_texts = 0;
	while (1)
	{
		*line = get_next_line(fd);
		if (!*line)
			break ;
		result = process_map_line(*line, map, &counter_clr, &counter_texts);
		if (result == 1)
			break ;
		else if (result == 2)
			return (c_malloc(0, 0), close(fd), 1);
	}
	if (!check_texture_completeness(*map))
		return (c_malloc(0, 0), close(fd), 1);
	return (0);
}

int	parse_map(char *str, t_map **map)
{
	int		fd;
	char	*line;

	if (handle_map_file_open(str, map, &fd))
		return (1);
	if (read_map_configuration(map, fd, &line))
		return (1);
	if (!parse_map_strct(*map, fd, line))
		return (c_malloc(0, 0), close(fd), 1);
	if (!find_player(*map))
		return (write(2, "Invalid starting pos\n", 21),
			c_malloc(0, 0), close(fd), 1);
	return (validate_map(*map));
}
