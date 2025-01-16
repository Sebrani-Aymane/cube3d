/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:14:51 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/12 05:27:33 by asebrani         ###   ########.fr       */
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
#include <math.h>
#include <string.h> 
#include <float.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
#  define HEIGHT 720
#  define WIDTH 1080
#  define FOV_ANGLE M_PI / 3
#  define NUM_RAYS WIDTH
# endif


typedef struct s_map_status
{
    int no_found;
    int so_found;
    int we_found;
    int ea_found;
} t_map_status;


typedef struct s_list
{
    char *line;
    
} t_list;

typedef struct s_map{
    int x_player_pos;
    int y_player_pos;
    char start_direction;
    char *no_texts;
    char *so_texts;
    char *we_texts;
    char *ea_texts;
    int floor_clr[3];
    int ceiling_clr[3];
    int             fd;
    char **mp_arrs;
    
    t_list *map_list;
}   t_map;

//if u would want some structure add and seperate textu frome ...

/////////////////Tracing structs

typedef struct s_keys
{
    int w_pressed;
    int s_pressed;
    int a_pressed;
    int d_pressed;
    int left_pressed;
    int right_pressed;
} t_keys;

typedef struct s_rays
{
    float distance;
    float ray_angle;
    float wallhitx;
    float wallhity;
    int hit_ver;
    int facing_up;
    int facing_down;
    int facing_left;
    int facing_right;
    float intarsec_x;
    float intersec_y;

} t_rays;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_lentgh;
    int endian;
    int range_ho_size;
    int range_ve_size;
    int player_x;
    int player_y;
    double player_angle;
    double move_speed;
    double rotation_speed;
    int flag;
    t_map *map;          
    t_keys keys;  
    t_rays rays[NUM_RAYS];
} t_mlx;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printer(char **str);

int parse_map_name(char *av);
int parse_map(char *av, t_map **map);
int	get_types_infos(char *line);
t_map *map_init(void);
t_map *check_texts(char *line, t_map *map);
int check_texture_completeness(t_map *map);
int is_valid_file(char *path);
int is_duplicate_direction(char *direction, t_map *map);
int	parse_color_line(char *line,t_map *map);
int parse_map_strct(t_map *map, int fd,char *line);
int find_player(t_map *map);
int validate_map(t_map *map);
int parse_map_grid(t_map *map);
void create_new_map(t_map **map);
////////////////////////////////////////////
int	ft_strncmp(char *s1, char *s2, int	n);
int ft_strcmp(char *s1, char *s2);
int     ft_strlenn(char *str);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
void free_split_array(char **arr);
char	**ft_splitt(char *s, char c);
int check_set_chars(char *str, char c);
char *ft_del_space(char *str);
int check_for_surrounds(int i,int j, char **map);
int count_map_rows(char **map);
char **replace_spaces_with_one(char **map);
/////////////////
int	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char *ft_strtrim(char  *s1, char  *set);
char	*ft_strchr(char *string, int c );
void	*ft_calloc(int count, int size);
char *ft_strchrr(char *s, int c);
char	*get_next_line(int fd);
int ft_strlcpy(char *dst, const char *src, int dstsize);

///////////////Tracing function

void	init_player(t_mlx *mlx, t_map *map);
void	render_frame(t_mlx *mlx);
void	move_player(t_mlx *mlx, int forward);
void	rotate_player(t_mlx *mlx, int clockwise);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_pov(t_map *map, t_mlx *mlx);
void	draw_tile(t_mlx *mlx, int x, int y, int range_ho_size, int range_ve_size, int color);
void	draw_grid(t_mlx *mlx, int cell_width, int cell_height);
void	draw2d(t_map *map, t_mlx *mlx);
void	calculate_endpoint(t_mlx *mlx, int length, double angle, int *x_end, int *y_end);
void	draw_line_dda(t_mlx *mlx, int x0, int y0, int x1, int y1, int color);
void	map_tracing(t_map *map, t_mlx *mlx);
void initialize_ray(t_rays *ray, float ray_angle);
void	initialize_mlx(t_mlx *mlx);
void    setup_hooks(t_mlx *mlx);
void find_horizontal_hit(t_mlx *mlx, t_rays *ray, float ray_angle, float *horz_x, float *horz_y, int *found);
void find_vertical_hit(t_mlx *mlx, t_rays *ray, float ray_angle, float *vert_x, float *vert_y, int *found);
void	initialize_map_settings(t_map *map, t_mlx *mlx);
void draw_walls(t_mlx *mlx);
void cast_rays(t_mlx *mlx);
float normal_angle(float angle);
int	close_wind(t_mlx *mlx);
int	is_valid_position(t_mlx *mlx, int new_x, int new_y);
int	key_press(int keycode, t_mlx *mlx);
int	key_release(int keycode, t_mlx *mlx);
int	game_loop(t_mlx *mlx);
int	ft_strlen2d(char **str);
int	key_press(int keycode, t_mlx *mlx);
int	key_release(int keycode, t_mlx *mlx);
int	game_loop(t_mlx *mlx);

#endif