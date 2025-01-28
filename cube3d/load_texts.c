/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:58:32 by asebrani          #+#    #+#             */
/*   Updated: 2025/01/28 20:03:47 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void load_texture(void *mlx_ptr, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width, &tex->height);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, 
                                 &tex->line_length, &tex->endian);
}
