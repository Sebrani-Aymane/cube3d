/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:05:46 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/23 23:02:08 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	validate_color_line(char *trimmed,int *clr_counter)
{

	if ((trimmed[0] != 'F' || trimmed[0] != 'C') && *clr_counter >= 2)
		return (write(2,
				"Error: Missing or incomplete color configurations\n", 49), 0);
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
	{
		if (!rgb_parts[part_count])
			return (0);
		part_count++;
	}
	if (part_count != 3)
		return (0);
	part_count = 0;
	while (part_count < 3)
	{
		if (!is_only_digits(rgb_parts[part_count]))
			return (0);
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

int	parse_color_line(char *line, t_map *map,int *clr_counter)
{
	char	*trimmed;
	char	*color_start;
	t_color	color;

	color.r = -1;
	color.g = -1;
	color.b = -1;
	trimmed = ft_strtrim(line, " \n\t");
	if (!trimmed)
		return(0);
	if (!validate_color_line(trimmed,clr_counter))
	{
		c_malloc(0, 0);
		return (0);
	}
	color_start = skip_space(trimmed + 1);
	if (!extract_rgb_values(color_start, &color))
		return (0);
	assign_color_to_map(line[0], map, color);
	return (1);
}
