/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:02:19 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/23 23:13:48 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	count_word(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static	int	norminet_split(char *s, int *i, char c, int *size)
{
	(*size) = 0;
	while (s[(*i)] == c && s[(*i)])
		(*i)++;
	while (s[(*i)] != c && s[(*i)])
	{
		(*size)++;
		(*i)++;
	}
	return (2001);
}

char	**ft_splitt(char *s, char c)
{
	char	**dst;
	int		i;
	int		l;
	int		size;

	if (!s)
		return (NULL);
	l = 0;
	i = 0;
	dst = (char **)c_malloc((count_word(s, c) + 1) * sizeof(char *), 1);
	if (!dst)
		return (NULL);
	while (l < count_word(s, c) && s[i])
	{
		norminet_split((char *)s, &i, c, &size);
		if (size > 0)
		{
			dst[l] = ft_substr(s, i - size, size);
			if (dst[l] == NULL)
				return (NULL);
			l++;
		}
	}
	dst[l] = ((void *)0);
	return (dst);
}

int	extract_rgb_values(char *color_start, t_color *color)
{
	char	**rgb_parts;

	if (!more_parsing(color_start))
		return (0);
	rgb_parts = ft_splitt(color_start, ',');
	if (!rgb_parts)
	{
		c_malloc(0, 0);
		return (0);
	}
	if (!parse_color_components(rgb_parts, &color->r, &color->g, &color->b))
	{
		c_malloc(0, 0);
		write(2, "Missing color configuration\n", 29);
		exit (0);
	}
	return (validate_color_range(color->r, color->g, color->b));
}

void	assign_color_to_map(char type, t_map *map, t_color color)
{
	if (type == 'F')
	{
		map->floor_clr[0] = color.r;
		map->floor_clr[1] = color.g;
		map->floor_clr[2] = color.b;
	}
	else if (type == 'C')
	{
		map->ceiling_clr[0] = color.r;
		map->ceiling_clr[1] = color.g;
		map->ceiling_clr[2] = color.b;
	}
}
