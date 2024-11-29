/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:33:58 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/29 22:18:24 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void free_split_array(char **arr)
{
    int i;

    if (!arr || !*arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int is_duplicate_direction(t_map_textures *head, char *direction)
{
    t_map_textures *current;

    if (!head || !direction)
        return (0);
    current = head;
    while (current)
    {
        if (ft_strcmp(current->direction, direction) == 0)
            return ( write(2,"a duplicated direction is found\n", 32),1);
        current = current->next;
    }
    return (0);
}

int is_valid_file(const char *path)
{
    return (access(path, R_OK) == 0);
}

void free_texture_list(t_map_textures *head)
{
    t_map_textures *current;
    t_map_textures *temp;

    current = head;
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp->direction);
        free(temp->path);
        free(temp);
    }
}

t_map_textures *create_first_texture_node(char **str)
{
    t_map_textures *node;

    node = malloc(sizeof(t_map_textures));
    if (!node)
        return (NULL);
    node->direction = ft_strdup(str[0]);
    node->path = ft_strdup(str[1]);
    node->next = NULL;
    return (node);
}

t_map_textures *add_new_texture_node(t_map *map, char **str)
{
    t_map_textures *new_node;

    if (is_duplicate_direction(map->map_texts, str[0]))
        return (NULL);

    if (!is_valid_file(str[1]))
    {
        write(2, "Error: Invalid file path for texture\n", 37);
        return (NULL);
    }

    new_node = malloc(sizeof(t_map_textures));
    if (!new_node)
    {
        write(2, "Error: Memory allocation failed\n", 33);
        return (NULL);
    }

    new_node->direction = ft_strdup(str[0]);
    new_node->path = ft_strdup(str[1]);
    new_node->next = map->map_texts;

    return (new_node);
}


t_map_textures *check_texts(char *line, t_map *map)
{
    char **str;
    int i = 0;
    int arr_len;

    if (!line || !map)
    {
        write(2, "Error: Invalid input to check_texts\n", 36);
        return (NULL);
    }
    str = ft_splitt(line, ' ');
    if (!str)
    {
        write(2, "Error: Failed to split line\n", 28);
        return (NULL);
    }
    arr_len = 0;
    while (str[i++])
        arr_len++;
    if (arr_len != 2)
    {
        write(2, "Error: Invalid texture definition\n", 34);
        free_split_array(str);
        return (NULL);
    }

    if (!is_valid_file(str[1]))
    {
        write(2, "Error: Cannot access texture file\n", 35);
        free_split_array(str);
        return (NULL);
    }

    if (is_duplicate_direction(map->map_texts, str[0]))
    {
        free_split_array(str);
        return (NULL);
    }

    t_map_textures *new_node = malloc(sizeof(t_map_textures));
    if (!new_node)
    {
        write(2, "Error: Memory allocation failed\n", 33);
        free_split_array(str);
        return (NULL);
    }
    new_node->direction = ft_strdup(str[0]);
    new_node->path = ft_strdup(str[1]);
    new_node->next = map->map_texts;
    map->map_texts = new_node;

    printf("Added texture node: %s -> %s\n", new_node->direction, new_node->path);
    free_split_array(str);
    return (map->map_texts);
}

