/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:39:30 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 11:51:56 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_init_textures(char *texture_name, t_image **texture, \
char *path, t_game *game)
{
	char	*path_t;
	int		fd;

	path_t = ft_strjoin(path, texture_name);
	if (path_t == NULL)
		ft_error_msg("Can't allocate path texture!\n");
	*texture = malloc(sizeof(**texture));
	if (*texture == NULL)
		ft_error_msg("Can't allocate image!\n");
	fd = open(path_t, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Can't open image!\n");
	close(fd);
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_t, \
		&((*texture)->width), &((*texture)->heigth));
	if ((*texture)->img == NULL)
		ft_error_msg("Can't create image!\n");
	ft_init_data(*texture);
	free(path_t);
}

void	ft_init_game_textures(t_game *game, char *exec)
{
	t_textures	*textures;

	textures = malloc(sizeof(*textures));
	if (textures == NULL)
		ft_error_msg("Can't allocate textures!\n");
	game->textures = textures;
	textures->path = malloc(sizeof(*textures->path) * \
	ft_strrchr_i(exec, '/') + 2);
	if (textures->path == NULL)
		ft_error_msg("Can't allocate textures->path!\n");
	ft_strlcpy(textures->path, exec, ft_strrchr_i(exec, '/') + 2);
	ft_init_textures(game->info->no_texture_name, &textures->north, \
	textures->path, game);
	ft_init_textures(game->info->so_texture_name, &textures->south, \
	textures->path, game);
	ft_init_textures(game->info->ea_texture_name, &textures->east, \
	textures->path, game);
	ft_init_textures(game->info->we_texture_name, &textures->west, \
	textures->path, game);
	ft_create_map_texture(&textures->map, game);
}

t_info	*ft_init_game_info(char *map_name)
{
	t_info	*info;

	info = malloc(sizeof(*info));
	if (info == NULL)
		ft_error_msg("Can't allocate info!\n");
	info->player = malloc(sizeof(t_player));
	if (info->player == NULL)
		ft_error_msg("Can't allocate player!\n");
	info->no_texture_name = NULL;
	info->so_texture_name = NULL;
	info->ea_texture_name = NULL;
	info->we_texture_name = NULL;
	info->ceiling_color = -1;
	info->floor_color = -1;
	ft_read_map_info(info, map_name);
	ft_find_player_pos(info);
	ft_check_map(info);
	ft_replace_void_map(info);
	info->map_square_size = ft_get_square_size(info);
	return (info);
}

t_bools	*ft_init_bools(void)
{
	t_bools	*bools;

	bools = malloc(sizeof(t_bools));
	bools->a = 0;
	bools->d = 0;
	bools->w = 0;
	bools->s = 0;
	bools->left = 0;
	bools->right = 0;
	bools->mouse = 0;
	return (bools);
}

t_game	*ft_init_game(char *map_name, char *exec)
{
	t_game	*game;

	game = malloc(sizeof(*game));
	if (game == NULL)
		ft_error_msg("Can't allocate game!\n");
	game->info = ft_init_game_info(map_name);
	game->bools = ft_init_bools();
	game->player = game->info->player;
	game->ray_x = malloc(sizeof(t_ray));
	if (!game->ray_x)
		ft_error_msg("Can't allocate ray!\n");
	game->ray_y = malloc(sizeof(t_ray));
	if (!game->ray_y)
		ft_error_msg("Can't allocate ray!\n");
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error_msg("Can't init mlx!\n");
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, GAME_NAME);
	if (game->mlx_win == NULL)
		ft_error_msg("Can't build mlx window!\n");
	ft_init_game_textures(game, exec);
	mlx_mouse_hide();
	return (game);
}
