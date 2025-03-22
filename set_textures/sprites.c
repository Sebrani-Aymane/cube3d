/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:41:31 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/22 03:33:03 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

#include "mlx.h"  


t_weapon_animation *init_weapon_animation(t_mlx *mlx)
{
    t_weapon_animation *weapon = c_malloc(sizeof(t_weapon_animation),1);
    if (!weapon)
        return (c_malloc(0,0),NULL);
    
    
    init_texture(mlx, &mlx->weapon.frames[0] , "textures/00.xpm");
    init_texture(mlx, &mlx->weapon.frames[1] , "textures/01.xpm");
    init_texture(mlx, &mlx->weapon.frames[2] , "textures/02.xpm");
    init_texture(mlx, &mlx->weapon.frames[3] , "textures/03.xpm");
    
    
    weapon->current_frame = 0;
    weapon->frame_counter = 0;
    weapon->is_attacking = 0;
    weapon->frame_delay = 6;  
    
    return weapon;
}


void weapon_attack(t_weapon_animation *weapon)
{
    if (!weapon->is_attacking)
    {
        weapon->is_attacking = 1;
        weapon->current_frame = 0;
        weapon->frame_counter = 0;
    }
}


void update_weapon_animation(t_weapon_animation *weapon)
{
    if (!weapon->is_attacking)
        return;
    
    weapon->frame_counter++;
    
    if (weapon->frame_counter >= weapon->frame_delay)
    {
        weapon->frame_counter = 0;
        weapon->current_frame++;
        
        
        if (weapon->current_frame >= 4)
        {
            weapon->current_frame = 0;
            weapon->is_attacking = 0;
        }
    }
}


void draw_weapon(t_mlx *mlx, t_weapon_animation *knife)
{
    t_texture *current_texture;
    int pos_x, pos_y;
    int tex_x, tex_y;
    int color;

    current_texture = &knife->frames[knife->current_frame];

    pos_x = (1200 / 2) - (current_texture->width / 2);
    pos_y = 720 - current_texture->height;

 int y = 0;
while (y < current_texture->height)
{
    int x = 0;
    while (x < current_texture->width)
    {
        tex_x = x;
        tex_y = y;

        color = get_texture_color(current_texture, tex_x, tex_y);

        if (color != 0x000000)
        {
            my_mlx_pixel_put(mlx->mlx, pos_x + x, pos_y + y, color);
        }
        x++; 
    }
    y++; 
}
}

void handle_weapon(t_mlx *mlx)
{
    if (!mlx->weapon.weapon)
        mlx->weapon.weapon = init_weapon_animation(mlx);
    
    t_weapon_animation *weapon = mlx->weapon.weapon;
    
    
    update_weapon_animation(weapon);
    draw_weapon(mlx, weapon);
}