/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:52 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/25 19:41:52 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int parse_map_name(char *av)
{
	int	len;

	len = ft_strlen(av);

	if ((av[len - 1] != 'b' || av[len - 2] != 'u'
		|| av[len - 3] != 'c' || av[len - 4] != '.'))
		return (0);
	return (1);
}

int	parse_line(char *line)
{
	if (line[0]<= '9' && line[0] >= '0'
		&& !get_map_data(line))
			return (0);
	else
		return (2)
	
	
}

int	parse_map(char *str)
{
	int 	fd;
	char	*line;
	char	*list;
	
	fd = open(str, fd | O_RDONLY);
	if (fd < 0)
		return (0);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if(!parse_line(line))
			break ;
		
	}
}