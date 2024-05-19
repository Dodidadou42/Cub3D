/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:28:10 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 10:24:16 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_check_map_close(char **map, unsigned int x, unsigned int y)
{
	if (map[y][x] == '0')
		map[y][x] = 'o';
	if ((x == 0) || (map[y][x - 1] == ' '))
		ft_error_msg("Map not closed!\n");
	else if (map[y][x - 1] == '0')
		ft_check_map_close(map, x - 1, y);
	if ((map[y][x + 1] == ' ') || (map[y][x + 1] == '\0'))
		ft_error_msg("Map not closed!\n");
	else if (map[y][x + 1] == '0')
		ft_check_map_close(map, x + 1, y);
	if ((y == 0) || x >= ft_strlen(map[y - 1]) || \
	(map[y - 1][x] == ' ') || (map[y - 1][x] == '\0'))
		ft_error_msg("Map not closed!\n");
	else if (map[y - 1][x] == '0')
		ft_check_map_close(map, x, y - 1);
	if ((map[y + 1] == NULL) || (x >= ft_strlen(map[y + 1])) || \
	(map[y + 1][x] == ' ') || (map[y + 1][x] == '\0'))
		ft_error_msg("Map not closed!\n");
	else if (map[y + 1][x] == '0')
		ft_check_map_close(map, x, y + 1);
}

void	ft_replace_original_map(char **map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'o')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	ft_check_map(t_info *info)
{
	unsigned int	x;
	unsigned int	y;
	char			**map;

	map = info->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] != '0') && (map[y][x] != '1') \
				&& (map[y][x] != ' '))
				ft_error_msg("Unknown character in the map!\n");
			x++;
		}
		y++;
	}
	ft_check_map_close(map, info->initial_pos_x, info->initial_pos_y);
	ft_replace_original_map(map);
}

unsigned int	ft_get_map_width(char **map)
{
	unsigned int	width;
	unsigned int	len;
	unsigned int	y;

	width = 0;
	y = 0;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		if (len > width)
			width = len;
		y++;
	}
	return (width);
}

void	ft_replace_void_map(t_info *info)
{
	unsigned int	y;
	unsigned int	x;
	char			*new_line;

	info->map_width = ft_get_map_width(info->map);
	y = 0;
	while (info->map[y])
	{
		new_line = malloc(sizeof(*new_line) * (info->map_width + 1));
		ft_strlcpy(new_line, info->map[y], ft_strlen(info->map[y]) + 1);
		x = ft_strlen(info->map[y]);
		while (x < info->map_width)
		{
			new_line[x] = ' ';
			x++;
		}
		new_line[x] = '\0';
		free(info->map[y]);
		info->map[y] = new_line;
		y++;
	}
}
