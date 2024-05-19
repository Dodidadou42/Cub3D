/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:52:00 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 13:53:59 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_put_floor_ceil_on_screen(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			ft_pixel_put_to_image(game->textures->screen->data, \
			j, i, game->info->ceiling_color);
		i++;
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			ft_pixel_put_to_image(game->textures->screen->data, \
			j, i, game->info->floor_color);
		i++;
	}
}

void	ft_display_textures(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_put_image_to_window(game->mlx, game->mlx_win, \
	game->textures->screen->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, \
	game->textures->map->img, WIDTH - (game->textures->map->width), \
	HEIGHT - (game->textures->map->heigth));
	ft_destroy_screen_texture(&game->textures->screen, game);
	ft_draw_player(game, 0xFFD700);
}

unsigned int	ft_get_pixel_color_in_image(t_data *image_data, \
int i_pixel_image, int j)
{
	unsigned int	add;
	unsigned int	*colors_ptr;
	unsigned int	colors_tab[3];
	unsigned int	colors;

	add = image_data->size_line * j / 4 + \
	image_data->bits_per_pixel / 32 * i_pixel_image;
	colors_ptr = (unsigned int *) image_data->addr + add;
	colors_tab[0] = colors_ptr[0] / 65536 % 256;
	colors_tab[1] = colors_ptr[1] / 256 % 256;
	colors_tab[2] = colors_ptr[2] % 256;
	colors = ft_convert_rgb_to_int(colors_tab);
	return (colors);
}

void	ft_display_column(int pixel[2], int i_pixel_image, \
t_image *image, t_game *game)
{
	unsigned int	colors;
	int				j;
	float			pixel_step;
	float			begin_j;

	if (pixel[0] <= HEIGHT)
		begin_j = 0;
	else
		begin_j = (pixel[0] - HEIGHT) / 2;
	pixel_step = (float) image->heigth / (float) pixel[0];
	j = 0;
	while (j + begin_j < pixel[0] - begin_j)
	{
		colors = ft_get_pixel_color_in_image(image->data, i_pixel_image, \
		floor(pixel_step * (j + begin_j)));
		if ((HEIGHT - pixel[0]) / 2 + j + begin_j < HEIGHT)
			ft_pixel_put_to_image(game->textures->screen->data, pixel[1], \
			(HEIGHT - pixel[0]) / 2 + j + begin_j, colors);
		j++;
	}
}
