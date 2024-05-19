/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:44:13 by ddychus           #+#    #+#             */
/*   Updated: 2023/05/03 16:30:48 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_draw_empty_square_on_image(int pos[2], int size,
	t_game *game, int color)
{
	int	p[4];

	p[0] = pos[0] / game->info->map_square_size;
	p[1] = pos[1] / game->info->map_square_size;
	p[2] = -1;
	while (++p[2] < size)
	{
		p[3] = -1;
		while (++p[3] < size)
		{
			if (((!p[1] || (p[1] && game->info->map[p[1] - 1][p[0]] == '0'))
				&& !p[3]) || (p[3] == size - 1
				&& (p[1] == (int)game->info->map_height - 1
				|| (p[1] < (int)game->info->map_height - 1
				&& game->info->map[p[1] + 1][p[0]] == '0'))) || (!p[2]
				&& (!p[0] || (p[0] && game->info->map[p[1]][p[0] - 1] == '0')))
				|| (p[2] == size - 1 && (p[0] == (int)game->info->map_width - 1
				|| (p[0] < (int)game->info->map_width - 1
				&& game->info->map[p[1]][p[0] + 1] == '0'))))
			{
				ft_pixel_put_to_image(game->textures->map->data,
					pos[0] + p[2], pos[1] + p[3], color);
			}
		}
	}
}

void	ft_draw_square_on_image(int pos[2], int size, t_game *game, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			ft_pixel_put_to_image(game->textures->map->data,
				pos[0] + i, pos[1] + j, color);
	}
}

void	ft_draw_square(int pos[2], int size, t_game *game, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	j = -1;
	x = pos[0];
	y = pos[1];
	while (++i < size)
	{
		while (++j < size)
		{
			mlx_pixel_put(game->mlx, game->mlx_win,
				x + i, y + j, color);
		}
		j = -1;
	}
}
