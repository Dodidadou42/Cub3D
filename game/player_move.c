/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:50:33 by ddychus           #+#    #+#             */
/*   Updated: 2023/05/04 16:36:40 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_check_next_cell(t_game *game, int var[4], float move_x, float move_y)
{
	if (game->info->map[var[1]][var[0]] == '1'
		|| game->info->map[var[3]][var[0]] == '1'
		|| game->info->map[var[1]][var[2]] == '1')
	{
		if (game->info->map[var[3]][var[0]] == '0')
			game->player->pos_x = move_x;
		if (game->info->map[var[1]][var[2]] == '0')
			game->player->pos_y = move_y;
		return ;
	}
	game->player->pos_x = move_x;
	game->player->pos_y = move_y;
}

void	ft_check_move(t_game *game, float move_x, float move_y)
{
	int	var[4];

	if (game->player->pos_x < move_x)
		var[0] = floor(move_x + 0.1);
	else if (game->player->pos_x > move_x)
		var[0] = floor(move_x - 0.1);
	else
		var[0] = floor(move_x);
	if (game->player->pos_y < move_y)
		var[1] = floor(move_y + 0.1);
	else if (game->player->pos_y > move_y)
		var[1] = floor(move_y - 0.1);
	else
		var[1] = floor(move_y);
	var[2] = floor(game->player->pos_x);
	var[3] = floor(game->player->pos_y);
	ft_check_next_cell(game, var, move_x, move_y);
}

void	ft_player_move(t_game *game, int key)
{
	float	move_x;
	float	move_y;

	if (key == KEY_W)
	{
		move_y = -(cos(game->player->vision * M_PI / 180) * 0.1);
		move_x = sin(game->player->vision * M_PI / 180) * 0.1;
	}
	else if (key == KEY_S)
	{
		move_y = cos(game->player->vision * M_PI / 180) * 0.1;
		move_x = -(sin(game->player->vision * M_PI / 180) * 0.1);
	}
	else if (key == KEY_A)
	{
		move_y = -(sin(game->player->vision * M_PI / 180) * 0.1);
		move_x = -(cos(game->player->vision * M_PI / 180) * 0.1);
	}
	else
	{
		move_y = sin(game->player->vision * M_PI / 180) * 0.1;
		move_x = cos(game->player->vision * M_PI / 180) * 0.1;
	}
	ft_check_move(game, game->player->pos_x + move_x,
		game->player->pos_y + move_y);
}

void	ft_vision_move(t_game *game, int key, int mouse)
{
	if (!key)
	{
		if (mouse == 1)
			game->player->vision -= 5;
		else if (mouse == 2)
			game->player->vision += 5;
	}
	else if (key == KEY_RIGHT)
		game->player->vision += 1;
	else if (key == KEY_LEFT)
		game->player->vision -= 1;
	while (game->player->vision >= 360)
		game->player->vision = game->player->vision - 360;
	while (game->player->vision < 0)
		game->player->vision = game->player->vision + 360;
}

void	ft_draw_player(t_game *game, int color)
{
	int	pos[2];

	pos[0] = WIDTH - (game->textures->map->width)
		+ game->player->pos_x * game->info->map_square_size - 1;
	pos[1] = HEIGHT - (game->textures->map->heigth)
		+ game->player->pos_y * game->info->map_square_size - 1;
	ft_draw_square(pos, 3, game, color);
}
