/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_check_map_close.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:03:15 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/03 18:22:28 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	ft_check_map_dir(char **map, unsigned int x, unsigned int y)
{
	if ((x == 0) || ((map[y][x - 1] != '0') && (map[y][x - 1] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((map[y][x + 1] != '0') && (map[y][x + 1] != '1'))
		ft_error_msg("Map not closed!\n");
	if ((y == 0) || x >= ft_strlen(map[y - 1]) || \
	((map[y - 1][x] != '0') && (map[y - 1][x] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((map[y + 1] == NULL) || (x >= ft_strlen(map[y + 1])) || \
	((map[y + 1][x] != '0') && (map[y + 1][x] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((x == 0) || (y == 0) || (x - 1) >= ft_strlen(map[y - 1]) || \
	((map[y - 1][x - 1] != '0') && (map[y - 1][x - 1] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((map[y + 1] == NULL) || (x + 1 >= ft_strlen(map[y + 1])) || \
	((map[y + 1][x + 1] != '0') && (map[y + 1][x + 1] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((y == 0) || x + 1 >= ft_strlen(map[y - 1]) || \
	((map[y - 1][x + 1] != '0') && (map[y - 1][x + 1] != '1')))
		ft_error_msg("Map not closed!\n");
	if ((x == 0) || (map[y + 1] == NULL) || \
	(x - 1 >= ft_strlen(map[y + 1])) || \
	((map[y + 1][x - 1] != '0') && (map[y + 1][x - 1] != '1')))
		ft_error_msg("Map not closed!\n");
}

void	ft_old_check_map_close(char **map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] != '0') && (map[y][x] != '1') \
				&& (map[y][x] != ' '))
				ft_error_msg("Unknown character in the map!\n");
			if (map[y][x] == '0')
				ft_check_map_dir(map, x, y);
			x++;
		}
		y++;
	}
}
