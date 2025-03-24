/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:52 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 22:20:16 by asebrani         ###   ########.fr       */
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

int	handle_textures(char *after, t_map **map, int *counter_texts)
{
	*map = check_texts(after, *map);
	if (!*map)
		return (0);
	(*counter_texts)++;
	return (1);
}

int	handle_colors(char *after, t_map **map, int *counter_clr)
{
	int	res;

	res = parse_color_line(after, *map, counter_clr);
	if (res)
		(*counter_clr)++;
	else if (res == 0)
		return (0);
	return (1);
}

int	process_map_line(char *line, t_map **map, int *counter_clr,
					int *counter_texts)
{
	char	*after;

	after = ft_strtrim(line, " \t");
	if (!after || *after == '\n')
		return (0);
	if ((*after == '1' || *after == '0')
		|| (*counter_clr == 2 && *counter_texts == 4))
		return (1);
	if (get_texts_infos(after))
		if (!handle_textures(after, map, counter_texts))
			return (2);
	if ((*counter_texts == 4 || *counter_texts == 0)
		&& (*after == 'F' || *after == 'C'))
		if (!handle_colors(after, map, counter_clr))
			return (2);
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
		return (c_malloc(0, 0), 1);
	if (!find_player(*map))
		return (write(2, "Invalid starting pos\n", 21),
			c_malloc(0, 0), 1);
	return (validate_map(*map));
}
