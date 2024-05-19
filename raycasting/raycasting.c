/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:46:22 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/03 18:46:26 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_raycasting(t_game *game)
{
	float	len_step;
	float	current_len;
	float	angle;
	int		i_pixel;

	current_len = tan((float) FOV / 2 * M_PI / 180);
	len_step = current_len * 2 / (float) WIDTH;
	i_pixel = 0;
	ft_create_screen_texture(&game->textures->screen, game);
	ft_put_floor_ceil_on_screen(game);
	while (i_pixel < WIDTH / 2)
	{
		angle = atan(current_len) * 180 / M_PI;
		ft_cast_ray(game, fmod(game->player->vision - angle, 360), i_pixel);
		current_len -= len_step;
		i_pixel++;
	}
	while (i_pixel < WIDTH)
	{
		angle = atan(current_len) * 180 / M_PI;
		ft_cast_ray(game, fmod(game->player->vision + angle, 360), i_pixel);
		current_len += len_step;
		i_pixel++;
	}
	ft_display_textures(game);
}
