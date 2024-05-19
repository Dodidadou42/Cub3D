/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:32:37 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 16:42:13 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define GAME_NAME "CUB3D"
# define HEIGHT 768
# define WIDTH 1080
# define FOV 70
# define MAP_SQUARE_SIZE 20

# define KEY_PRESS			02
# define KEY_RELEASE		03

# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_LEFT			123
# define KEY_W 				13
# define KEY_D 				2
# define KEY_S 				1
# define KEY_A 				0
# define KEY_ESCAPE 		53

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>

typedef struct s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_data;

typedef struct Player
{
	float			pos_x;
	float			pos_y;
	float			vision;
}			t_player;

typedef struct Ray
{
	float		delta_diag_dist;
	float		side_diag_dist;
	float		pos_x;
	float		pos_y;
	float		delta_line_dist;
	float		side_line_dist;
	float		traveled_dist;
	int			i;
}			t_ray;

typedef struct Information
{
	unsigned int	floor[3];
	unsigned int	ceiling[3];
	int				floor_color;
	int				ceiling_color;
	int				map_square_size;
	char			*no_texture_name;
	char			*so_texture_name;
	char			*we_texture_name;
	char			*ea_texture_name;
	char			**map;
	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	initial_pos_x;
	unsigned int	initial_pos_y;
	t_player		*player;
}			t_info;

typedef struct Image
{
	void	*img;
	int		width;
	int		heigth;
	t_data	*data;
}			t_image;

typedef struct Textures
{
	char			*path;
	t_image			*north;
	t_image			*south;
	t_image			*west;
	t_image			*east;
	t_image			*map;
	t_image			*screen;
}					t_textures;

typedef struct Bools
{
	int	w;
	int	s;
	int	d;
	int	a;
	int	left;
	int	right;
	int	mouse;
}			t_bools;

typedef struct Game
{
	void		*mlx;
	void		*mlx_win;
	t_textures	*textures;
	t_info		*info;
	t_player	*player;
	t_ray		*ray_x;
	t_ray		*ray_y;
	t_bools		*bools;
}				t_game;

//GAME UTILS
int		ft_handle_keyboard_input(t_game *game);
int		ft_handle_keyrelease(int key, t_game *game);
int		ft_handle_keypress(int key, t_game *game);

t_game	*ft_parsing(int argc, char **argv);
t_game	*ft_init_game(char *map_name, char *exec);
void	ft_game_loop(t_game *game);
int		ft_close_game(t_game *game);

//TEXTURE PARSING
void	ft_analyse_dir(char **name, char *line);
void	ft_analyse_floor_ceilling(unsigned int (*color)[3], char *line);

void	ft_create_map_texture(t_image **texture, t_game *game);
void	ft_create_screen_texture(t_image **texture, t_game *game);
void	ft_destroy_screen_texture(t_image **texture, t_game *game);
void	ft_init_data(t_image *image);

//MAP PARSING
void	ft_check_textures_numbers(char *line, unsigned int *line_i, \
unsigned int *nb_elem, int *no_nl);
void	ft_read_map_info(t_info *info, char *map_info);
void	ft_check_map(t_info *info);
void	ft_check_map_close(char **map, unsigned int x, unsigned int y);
void	ft_find_player_pos(t_info *info);
void	ft_replace_void_map(t_info *info);
void	ft_old_check_map_close(char **map);

//RAYCASTING UTILS
float	ft_get_delta_dist_y(float vision);
float	ft_get_delta_dist_x(float vision);
float	ft_get_side_dist_y(float pos_x, float vision);
float	ft_get_side_dist_x(float pos_y, float vision);

//RAYCASTING
void	ft_raycasting(t_game *game);
void	ft_cast_ray(t_game *game, float vision, int i_pixel);
void	ft_get_ray_dist_x(t_ray *ray_info, float vision);
void	ft_get_ray_dist_y(t_ray *ray_info, float vision);
int		ft_check_wall_x(t_game *game, float vision, int i_pixel);
int		ft_check_wall_y(t_game *game, float vision, int i_pixel);

//MOVE
void	ft_player_move(t_game *game, int key);
void	ft_vision_move(t_game *game, int key, int mouse);
void	ft_draw_player(t_game *game, int color);

//MLX UTILS
void	ft_draw_square(int pos[2], int size, t_game *game, int color);
void	ft_draw_square_on_image(int pos[2], int size, t_game *game, int color);
void	ft_draw_empty_square_on_image(int pos[2], int size, \
t_game *game, int color);
void	ft_pixel_put_to_image(t_data *data, int x, int y, int color);
int		ft_convert_rgb_to_int(unsigned int colors[3]);
void	ft_display_textures(t_game *game);
void	ft_put_floor_ceil_on_screen(t_game *game);
void	ft_display_column(int pixel[2], int i_pixel_image, \
t_image *image, t_game *game);
int		ft_get_square_size(t_info *info);

#endif