/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_map_screen.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:01:32 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/03 18:30:26 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_init_data(t_image *image)
{	
	image->data = malloc(sizeof(*(image->data)));
	image->data->addr = mlx_get_data_addr(image->img, \
&image->data->bits_per_pixel, &image->data->size_line, \
&image->data->endian);
	if (image->data->addr == NULL)
		ft_error_msg("Can't analyse image\n");
}

int	ft_draw_image_minimap(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	int				pos[2];

	y = -1;
	while (++y < game->info->map_height)
	{
		x = -1;
		while (++x < game->info->map_width)
		{
			pos[0] = x * game->info->map_square_size;
			pos[1] = y * game->info->map_square_size;
			if (game->info->map[y][x] == '1')
			{
				ft_draw_square_on_image(pos, \
				game->info->map_square_size, game, 0xD3D3D3);
				ft_draw_empty_square_on_image(pos, \
				game->info->map_square_size, game, 0x000000);
			}
			if (game->info->map[y][x] == '0')
				ft_draw_square_on_image(pos, \
				game->info->map_square_size, game, 0x696969);
		}
	}
	return (0);
}

void	ft_create_map_texture(t_image **texture, t_game *game)
{
	*texture = malloc(sizeof(**texture));
	if (*texture == NULL)
		ft_error_msg("Can't allocate image!\n");
	(*texture)->width = game->info->map_width * game->info->map_square_size;
	(*texture)->heigth = game->info->map_height * game->info->map_square_size;
	(*texture)->img = mlx_new_image(game->mlx, \
	(*texture)->width, (*texture)->heigth);
	ft_init_data(*texture);
	ft_draw_image_minimap(game);
}

void	ft_destroy_screen_texture(t_image **texture, t_game *game)
{
	mlx_destroy_image(game->mlx, (*texture)->img);
	free((*texture)->data);
	free((*texture));
}

void	ft_create_screen_texture(t_image **texture, t_game *game)
{
	*texture = malloc(sizeof(**texture));
	if (*texture == NULL)
		ft_error_msg("Can't allocate image!\n");
	(*texture)->width = WIDTH;
	(*texture)->heigth = HEIGHT;
	(*texture)->img = mlx_new_image(game->mlx, \
	(*texture)->width, (*texture)->heigth);
	ft_init_data(*texture);
}
