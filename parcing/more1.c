/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:34:20 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/23 23:06:53 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	return (result);
}

int more_parsing(char*str)
{
	int	i;
	i = 0;
	while (str[i])
	{

		if (str[i] == ',' &&  str[i + 1] && str[ i + 1] == ',')
			return (write(2,"error in colors\n",16),0);

		if (str[i] == ',' && (!str[i+1] || !is_only_digits(str))){
			return ((write(2,"error in colors\n", 16),0));}
		i++;
	}
	return (1);
}