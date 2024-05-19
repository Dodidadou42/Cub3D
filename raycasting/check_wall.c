/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:15:30 by ddychus           #+#    #+#             */
/*   Updated: 2023/05/04 13:53:57 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

float	ft_get_wall_height(t_game *game, float vision, int check)
{
	float	angle;
	float	height;

	if (vision <= game->player->vision)
		angle = 90 - (game->player->vision - vision);
	else
		angle = 90 - (vision - game->player->vision);
	if (!check)
		height = sin(angle * M_PI / 180) * game->ray_x->traveled_dist;
	else
		height = sin(angle * M_PI / 180) * game->ray_y->traveled_dist;
	return (height);
}

void	ft_check_wall_y_next(t_game *game, float vision, int i_pixel, int y)
{
	float	height;
	float	wall_height;
	int		pixel[2];

	wall_height = ft_get_wall_height(game, vision, 1);
	height = (float) HEIGHT / wall_height;
	pixel[0] = height;
	pixel[1] = i_pixel;
	if (0 <= vision && vision <= 180)
		ft_display_column(pixel, floor((game->ray_y->pos_y - y) * \
		game->textures->east->width), game->textures->east, game);
	else
		ft_display_column(pixel, floor((1 - (game->ray_y->pos_y - y)) * \
		game->textures->west->width), game->textures->west, game);
	return ;
}

int	ft_check_wall_y(t_game *game, float vision, int i_pixel)
{
	int	x;
	int	y;

	if (0 <= vision && vision <= 180)
		x = game->ray_y->pos_x;
	else
		x = game->ray_y->pos_x - 1;
	y = floor(game->ray_y->pos_y);
	if (x < -10 || y < -10 || x > (int) game->info->map_width + 10
		|| y > (int)game->info->map_height + 10)
		return (0);
	else if (x < 0 || y < 0 || x > (int) game->info->map_width -1
		|| y > (int) game->info->map_height - 1)
		return (1);
	else if (game->info->map[y][x] == '1')
	{
		ft_check_wall_y_next(game, vision, i_pixel, y);
		return (0);
	}
	return (1);
}

void	ft_check_wall_x_next(t_game *game, float vision, int i_pixel, int x)
{
	float	height;
	float	wall_height;
	int		pixel[2];

	wall_height = ft_get_wall_height(game, vision, 0);
	height = (float) HEIGHT / wall_height;
	pixel[0] = height;
	pixel[1] = i_pixel;
	if (90 <= vision && vision <= 270)
		ft_display_column(pixel, floor((1 - (game->ray_x->pos_x - x)) * \
		game->textures->north->width), game->textures->north, game);
	else
		ft_display_column(pixel, floor((game->ray_x->pos_x - x) * \
		game->textures->south->width), game->textures->south, game);
	return ;
}

int	ft_check_wall_x(t_game *game, float vision, int i_pixel)
{
	int	x;
	int	y;

	if (90 <= vision && vision <= 270)
		y = game->ray_x->pos_y;
	else
		y = game->ray_x->pos_y - 1;
	x = floor(game->ray_x->pos_x);
	if (x < -10 || y < -10 || x > (int) game->info->map_width + 9
		|| y > (int) game->info->map_height + 9)
		return (0);
	else if (x < 0 || y < 0 || x > (int) game->info->map_width - 1
		|| y > (int) game->info->map_height - 1)
		return (1);
	else if (game->info->map[y][x] == '1')
	{
		ft_check_wall_x_next(game, vision, i_pixel, x);
		return (0);
	}
	return (1);
}
