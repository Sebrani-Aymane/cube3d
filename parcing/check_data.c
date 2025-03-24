/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:19:56 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 04:19:41 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || *str == '\0')
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',')
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

int	is_valid_file(char *path)
{
	char	*str;

	str = ft_strtrim(path, "\n");
	if (access(str, F_OK | R_OK) == 0)
		return (1);
	return (0);
}

int	is_safe_to_parse(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'N' || str[i] == 'E' || str[i] == 'W' || str[i] == 'S'
		|| str[i] == 'F' || str[i] == 'C' || str[i] == '\n')
		return (0);
	else
		return (1);
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
		if (!*line || is_safe_to_parse(*line))
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
