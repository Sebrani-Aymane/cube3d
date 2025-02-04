/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:58:32 by asebrani          #+#    #+#             */
/*   Updated: 2025/02/04 21:21:12 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

unsigned int get_texture_color(t_texture *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    
    int position = (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    

    unsigned char *ptr = (unsigned char *)texture->addr;
    
        return ((unsigned int)ptr[position + 3] << 24 |  
                (unsigned int)ptr[position + 2] << 16 |  
                (unsigned int)ptr[position + 1] << 8  |  
                (unsigned int)ptr[position] << 0);          
}

int init_texture(void *mlx, t_texture *texture, char *path)
{

    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    

    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, 
                                    &texture->line_length, &texture->endian);
    if (!texture->addr)
    {
        mlx_destroy_image(mlx, texture->img);
        return (0);
    }
    
    return (1);
}
