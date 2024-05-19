/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:04:17 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/03 18:41:31 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_handle_mouse_input(int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_mouse_get_pos(game->mlx_win, &x, &y);
	if (x < WIDTH / 2)
		game->bools->mouse = 1;
	else if (x > WIDTH / 2)
		game->bools->mouse = 2;
	return (0);
}

void	ft_game_loop(t_game *game)
{
	mlx_mouse_move(game->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(game->mlx_win, KEY_PRESS, (1L << 0), ft_handle_keypress, game);
	mlx_hook(game->mlx_win, KEY_RELEASE, (1L << 1), ft_handle_keyrelease, game);
	mlx_hook(game->mlx_win, 06, (1L << 6), ft_handle_mouse_input, game);
	mlx_loop_hook(game->mlx, ft_handle_keyboard_input, game);
	mlx_hook(game->mlx_win, 17, 0, ft_close_game, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_parsing(argc, argv);
	ft_raycasting(game);
	ft_game_loop(game);
	return (0);
}
