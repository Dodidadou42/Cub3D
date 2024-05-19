/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:37 by ddychus           #+#    #+#             */
/*   Updated: 2023/05/04 16:43:33 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_get_square_size(t_info *info)
{
	int	max_width;
	int	max_height;

	max_width = WIDTH / 5 / info->map_width;
	max_height = HEIGHT / 4 / info->map_height;
	if (max_width < max_height)
		return (max_width);
	else
		return (max_height);
}

void	ft_free_destroy_image(t_game *game, t_image *image)
{
	free(image->data);
	mlx_destroy_image(game->mlx, image->img);
	free(image);
}

void	ft_free_textures(t_game *game)
{
	free(game->textures->path);
	ft_free_destroy_image(game, game->textures->north);
	ft_free_destroy_image(game, game->textures->south);
	ft_free_destroy_image(game, game->textures->east);
	ft_free_destroy_image(game, game->textures->west);
	ft_free_destroy_image(game, game->textures->map);
	free(game->textures);
}

int	ft_close_game(t_game *game)
{
	int	i;

	i = -1;
	while (game->info->map[++i])
		free(game->info->map[i]);
	free(game->info->map);
	free(game->info->player);
	free(game->info->no_texture_name);
	free(game->info->so_texture_name);
	free(game->info->we_texture_name);
	free(game->info->ea_texture_name);
	free(game->info);
	free(game->ray_x);
	free(game->ray_y);
	free(game->bools);
	ft_free_textures(game);
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_window(game->mlx, game->mlx_win);
	free(game);
	exit(0);
}
