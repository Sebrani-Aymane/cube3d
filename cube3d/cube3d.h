/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:14:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/30 11:52:39 by asebrani         ###   ########.fr       */
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



typedef struct s_map_status
{
    int no_found;
    int so_found;
    int we_found;
    int ea_found;
} t_map_status;

    
typedef struct s_list{
    
    char *type;
    char *info;
    struct s_list *next;
    
} t_list;

typedef struct s_map{
    char *no_texts;
    char *so_texts;
    char *we_texts;
    char *ea_texts;
    int floor_clr[3];
    int ceiling_clr[3];
    int             fd;
}   t_map;

int parse_map_name(char *av);
int parse_map(char *av);
int	get_types_infos(char *line);
void map_init(t_map *map);
t_map *check_texts(char *line, t_map *map);
int check_texture_completeness(t_map *map);
int is_duplicate_direction(char *direction, t_map *map);

/////////////////
int	ft_strncmp(char *s1, char *s2, int	n);
int ft_strcmp(char *s1, char *s2);
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