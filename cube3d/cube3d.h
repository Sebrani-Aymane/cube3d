/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:14:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/25 19:03:40 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"

typedef struct s_list{
    char *type;
    char *info;
    struct s_list *next;
    
} t_list;

int parse_map_name(char *av);


/////////////////
int     ft_strlen(char *str);
char	**ft_split(char const *s, char c);
#endif