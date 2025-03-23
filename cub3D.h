/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:06:57 by kaafkhar          #+#    #+#             */
/*   Updated: 2025/03/23 10:35:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 10
# define HEIGHT 720
# define WIDTH 1200
# define FOV_ANGLE M_PI / 3
# define NUM_RAYS WIDTH

# include "unistd.h"
# include "stdio.h"
# include "fcntl.h"
# include "stdlib.h"
# include "mlx.h"
# include "limits.h"
# include "math.h"
# include "string.h"
# include "float.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_coll
{
	void			*ptr;
	struct s_coll	*next;
}	t_coll;

typedef struct s_map_status
{
	int	no_found;
	int	so_found;
	int	we_found;
	int	ea_found;
}	t_map_status;

typedef struct s_list
{
	char	*line;
}	t_list;

typedef struct s_map
{
	int		x_player_pos;
	int		y_player_pos;
	char	start_direction;
	char	*no_texts;
	char	*so_texts;
	char	*we_texts;
	char	*ea_texts;
	int		floor_clr[3];
	int		ceiling_clr[3];
	int		fd;
	char	**mp_arrs;
	t_list	*map_list;
}	t_map;

typedef struct s_ray_params
{
	float	ray_angle;
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
}	t_ray_params;

typedef struct s_horz_params
{
	float	ray_angle;
	float	y_intercept;
	float	x_intercept;
	float	y_step;
	float	x_step;
}	t_horz_params;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	left_pressed;
	int	right_pressed;
	int	middle_pressed;
}	t_mouse;

typedef struct s_keys
{
	int	w_pressed;
	int	s_pressed;
	int	a_pressed;
	int	d_pressed;
	int	left_pressed;
	int	attack;
	int	right_pressed;
}	t_keys;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct s_draw_data
{
	int		wall_top;
	int		wall_bottom;
	float	wall_height;
	double	tex_offset;
	int		y;
}	t_draw_data;

typedef struct s_hit_points
{
	float	horz_x;
	float	horz_y;
	float	vert_x;
	float	vert_y;
	int		found_horz;
	int		found_vert;
}	t_hit_points;

typedef struct s_weapon_animation
{
	t_texture					frames[4];
	int							current_frame;
	int							frame_counter;
	int							is_attacking;
	struct s_weapon_animation	*weapon;
	int							frame_delay;
}	t_weapon_animation;

typedef struct s_rays
{
	float	distance;
	float	ray_angle;
	float	wallhitx;
	float	wallhity;
	float	intersec_y;
	float	intarsec_x;
	int		hit_ver;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
}	t_rays;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_lentgh;
	int					endian;
	int					flag;
	int					range_ho_size;
	int					range_ve_size;
	int					player_x;
	int					player_y;
	double				player_angle;
	double				move_speed;
	double				rotation_speed;
	unsigned int		ceiling_color;
	unsigned int		floor_color;
	t_map				*map;
	t_keys				keys;
	t_rays				rays[NUM_RAYS];
	t_textures			texs;
	t_weapon_animation	weapon;
	t_mouse				mouse;
}	t_mlx;

/* String utility functions */
int				ft_strncmp(char *s1, char *s2, int n);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlenn(char *str);
char			*ft_strdup(char *s1);
char			*ft_substr(char *s, int start, int len);
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strtrim(char *s1, char *set);
char			*ft_strchr(char *string, int c);
char			*ft_strchrr(char *s, int c);
int				ft_strlcpy(char *dst, const char *src, int dstsize);

/* Memory utility functions */
void			*c_malloc(size_t size, int flag);
void			*ft_calloc(int count, int size);
void			free_split_array(char **arr);

/* Parsing functions */
int				is_only_digits(char *str);
int				ft_atoi(const char *str);
int				get_texts_infos(char *line);
void			assign_color_to_map(char type, t_map *map, t_color color);
int				extract_rgb_values(char *color_start, t_color *color);
int				validate_color_range(int r, int g, int b);
int				parse_color_components(char **rgb_parts,
					int *r, int *g, int *b);
int				parse_map_name(char *av);
int				parse_map(char *av, t_map **map);
int				get_types_infos(char *line);
t_map			*map_init(void);
t_map			*check_texts(char *line, t_map *map);
int				check_texture_completeness(t_map *map);
int				is_valid_file(char *path);
int				is_duplicate_direction(char *direction, t_map *map);
int				parse_color_line(char *line, t_map *map);
int				parse_map_strct(t_map *map, int fd, char *line);
int				find_player(t_map *map);
int				validate_map(t_map *map);
int				parse_map_grid(t_map *map);
void			create_new_map(t_map **map);
char			**ft_splitt(char *s, char c);
int				check_set_chars(char *str, char c);
char			*ft_del_space(char *str);
int				check_for_surrounds(int i, int j, char **map);
int				count_map_rows(char **map);
char			**replace_spaces_with_one(char **map);
char			*get_next_line(int fd);

/* Raycasting functions */
void			map_tracing(t_map *map, t_mlx *mlx);
void			initialize_mlx(t_mlx *mlx);
void			initialize_map_settings(t_map *map, t_mlx *mlx);
void			init_player(t_mlx *mlx, t_map *map);
void			draw_weapon(t_mlx *mlx);
void			init_player_rays(t_mlx *mlx);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int				close_wind(t_mlx *mlx);
int				ft_strlen2d(char **str);
void			render_frame(t_mlx *mlx);
void			place_player(t_map *map, t_mlx *mlx);
void			initialize_cell_sizes(t_mlx *mlx);
void			set_player_position(t_map *map, t_mlx *mlx);
void			cast_rays(t_mlx *mlx);
float			normal_angle(float angle);
void			initialize_ray(t_rays *ray, float ray_angle);
void			draw_wall(t_mlx *mlx, int strip_id);
void			prepare_wall_texture(t_mlx *mlx, int strip_id,
					t_texture **texture, double *tex_x);
void			finalize_ray(t_rays *ray, float ray_angle, float player_angle);
void			choose_closest_hit(t_rays *ray,
					t_hit_points *hit, t_player *player);
float			calculate_distance(float x1, float y1, float x2, float y2);
unsigned int	*get_pixels(unsigned char *img, int len);
unsigned int	convert_bytes_to_int(unsigned char *img, int *i);
void			find_horizontal_hit(t_mlx *mlx, t_rays *ray,
					float ray_angle, t_hit_points *hit);
void			find_vertical_hit(t_mlx *mlx, t_rays *ray,
					float ray_angle, t_hit_points *hit);

/* Input handling */
void			setup_hooks(t_mlx *mlx);
int				key_press(int keycode, t_mlx *mlx);
int				key_release(int keycode, t_mlx *mlx);
int				game_loop(t_mlx *mlx);
void			rotate_player(t_mlx *mlx, int clockwise);
void			strafe_player(t_mlx *mlx, int right);
void			move_player(t_mlx *mlx, int forward);
int				is_valid_position(t_mlx *mlx, int new_x, int new_y);
void			update_position(t_mlx *mlx, int new_x, int new_y);

/* Texture handling */
unsigned int	get_texture_color(t_texture *texture, int x, int y);
int				init_texture(void *mlx, t_texture *texture, char *path);
void			set_textures(t_map *map, t_mlx *mlx);
void			handle_weapon(t_mlx *mlx);
void			update_weapon_animation(t_weapon_animation *weapon);

#endif