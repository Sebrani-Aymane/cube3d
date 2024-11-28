/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:33:58 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/28 15:30:58 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_map_textures *check_texts(char *line,t_map *map)
{
   // t_map_textures *map_texts;
    char **str;
    (void)map;
    str = ft_splitt(line,' ');
    printf("%s\n%s",str[0],str[1]);
    return(NULL);
}