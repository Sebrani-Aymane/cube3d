/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:09:31 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/06 23:04:52 by asebrani         ###   ########.fr       */
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

char **parse_map_strct(t_map *map, int fd,char *line)
{
    char **map_grid;
    int i;
    int j;
    char	*temp;
	char	*join;
    i = j = 0;
	(void)map;
	temp = NULL;
	join = ft_strdup("");
	if (*line == '1' || *line == '0')
		temp = line;
	else 
		temp = get_next_line(fd);
	if (!temp)
		return(write(2,"Error map!\n",12), close(fd),NULL);
	while (temp)
	{
		join = ft_strjoin(join, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	if (check_double_lines(join))
		return (free(join), NULL);
	map_grid = ft_splitt(join, '\n');
	free(join);
	return (map_grid);
}