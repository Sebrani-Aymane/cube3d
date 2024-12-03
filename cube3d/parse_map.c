/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:09:31 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/03 02:38:38 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int	check_double_lines(char *str)
{
	if (!str)
		return (write(2,"map error\n", 10), 1);
	if (str[ft_strlen(str) - 1] == '\n')
		return (1);
	while (*str)
	{
		if (*str == '\n' && *str == *(str + 1))
			return (1);
		str++;
	}
	return (0);
}

char **parse_map_strct(t_map *map, int fd,char *line,int flag)
{
    char **map_grid;
    int i;
    int j;
    char	*temp;
	char	*join;
    i = j = 0;

	temp = NULL;
	join = ft_strdup("");
	temp = get_next_line(fd);
	if (!temp)
		(ft_puterror("Error map!\n"), close(fd));
	while (temp)
	{
		join = ft_strjoinn(join, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	if (check_double_lines(join))
		return (free(join), NULL);
	map = ft_split(join, '\n');
	free(join);
	return (map);
    if (flag)
}