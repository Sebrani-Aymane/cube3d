/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:14:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/28 05:38:50 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_map_textures{
    char *path;
    char *direction;
    int  fd;
    struct s_map_textures *next;
    } t_map_textures;


typedef struct s_map_colors{
    char color;
    int r;
    int g;
    int b;
    int fd;
}t_map_color;
    
typedef struct s_list{
    
    char *type;
    char *info;
    struct s_list *next;
    
} t_list;

typedef struct s_map{
    t_map_textures *map_texts;
    t_map_color     *map_clrs;
    int             fd;
}   t_map;

int parse_map_name(char *av);
int parse_map(char *av);
int	get_types_infos(char *line);
t_map_textures *check_texts(char *line, t_map *map);

/////////////////
int	ft_strncmp(char *s1, char *s2, int	n);
int     ft_strlenn(char *str);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
char	**ft_splitt(char *s, char c);
char *ft_del_space(char *str);
/////////////////
int	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *string, int c );
void	*ft_calloc(int count, int size);
char	*get_next_line(int fd);

#endif