/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:19:56 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/05 23:44:51 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
int is_only_digits(char *str)
{
	int i=0;
    if (str == NULL || *str == '\0') {
        return (0);
    }
    while (str[i] != '\0') 
	{
        if (str[i] < '0' || str[i] > '9')
            return (0);
		i++;
    }
    return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > INT_MAX)
			return (-1);
		if (result * sign < INT_MIN)
			return (-1);
		i++;
	}
	return ((int)(result * sign));
}

int	validate_color_line(char *trimmed)
{
	if (!trimmed)
		return (0);
	if (trimmed[0] != 'F' && trimmed[0] != 'C')
		return (0);
	return (1);
}

char	*skip_space(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	parse_color_components(char **rgb_parts, int *r, int *g, int *b)
{
	int	part_count;

	part_count = 0;
	while (rgb_parts[part_count])
		part_count++;
	if (part_count != 3)
		return (0);
	part_count=0;

	while (part_count < 3)
	{
		if(!is_only_digits(rgb_parts[part_count]))
			return(0);
			part_count++;
	}
	*r = ft_atoi(rgb_parts[0]);
	*g = ft_atoi(rgb_parts[1]);
	*b = ft_atoi(rgb_parts[2]);
	return (1);
}

int	validate_color_range(int r, int g, int b)
{
	return (!(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255));
}
int	parse_color_line(char *line,t_map *map)
{
	char	*trimmed;
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;


	trimmed = ft_strtrim(line, " \n\t");
	if (!validate_color_line(trimmed))
	{
		c_malloc(NULL,0);
		return (0);
	}
	char *color_start = skip_space(trimmed + 1);
	rgb_parts = ft_splitt(color_start, ',');
	if (!rgb_parts)
	{
		c_malloc(NULL,0);
		return (0);
	}
	if (!parse_color_components(rgb_parts, &r, &g, &b))
	{
		free_split_array(rgb_parts);
		c_malloc(NULL,0);
		return (0);
	}
	free_split_array(rgb_parts);
	c_malloc(NULL,0);
	if (!validate_color_range(r, g, b))
		return (0);
	if (line[0] == 'F')
	{
		map->floor_clr[0] = r;
		map->floor_clr[1] = g;
		map->floor_clr[2] = b;
	}
	else if (line[0] == 'C')
	{
		map->ceiling_clr[0] = r;
		map->ceiling_clr[1] = g;
		map->ceiling_clr[2] = b;
	}
	return (1);
}
int is_valid_file(char *path)
{
	char *str;
	str = ft_strtrim(path,"\n");
	
    if (access(str, F_OK| R_OK) == 0)
        return 1; 
    return 0;
}


