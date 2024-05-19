/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:37:51 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/03 18:43:29 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_check_mouse_move(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx_win, &x, &y);
	if (x == WIDTH / 2)
		game->bools->mouse = 0;
}

void	ft_handle_keyboard_input2(t_game *game)
{
	if (game->bools->w == 1)
		ft_player_move(game, KEY_W);
	if (game->bools->s == 1)
		ft_player_move(game, KEY_S);
	if (game->bools->d == 1)
		ft_player_move(game, KEY_D);
	if (game->bools->a == 1)
		ft_player_move(game, KEY_A);
	if (game->bools->right == 1)
		ft_vision_move(game, KEY_RIGHT, 0);
	if (game->bools->left == 1)
		ft_vision_move(game, KEY_LEFT, 0);
	if (game->bools->mouse)
		ft_vision_move(game, 0, game->bools->mouse);
	mlx_mouse_move(game->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_clear_window(game->mlx, game->mlx_win);
	ft_raycasting(game);
}

int	ft_handle_keyboard_input(t_game *game)
{
	ft_check_mouse_move(game);
	if (!game->bools->a && !game->bools->d && !game->bools->s
		&& !game->bools->w && !game->bools->left && !game->bools->right
		&& !game->bools->mouse)
		return (0);
	else
		ft_handle_keyboard_input2(game);
	return (0);
}

int	ft_handle_keyrelease(int key, t_game *game)
{
	if (key == KEY_W)
		game->bools->w = 0;
	if (key == KEY_S)
		game->bools->s = 0;
	if (key == KEY_A)
		game->bools->a = 0;
	if (key == KEY_D)
		game->bools->d = 0;
	if (key == KEY_RIGHT)
		game->bools->right = 0;
	if (key == KEY_LEFT)
		game->bools->left = 0;
	return (0);
}

int	ft_handle_keypress(int key, t_game *game)
{
	if (key == KEY_W)
		game->bools->w = 1;
	if (key == KEY_S)
		game->bools->s = 1;
	if (key == KEY_A)
		game->bools->a = 1;
	if (key == KEY_D)
		game->bools->d = 1;
	if (key == KEY_RIGHT)
		game->bools->right = 1;
	if (key == KEY_LEFT)
		game->bools->left = 1;
	if (key == KEY_ESCAPE)
		ft_close_game(game);
	return (0);
}
