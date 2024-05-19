/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:32:18 by vdelafos          #+#    #+#             */
/*   Updated: 2023/04/26 19:12:05 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_set_player_pos(t_info *info, unsigned int pos[2], \
unsigned int *find_player, float vision)
{
	info->player->pos_x = pos[1] + 0.5;
	info->player->pos_y = pos[0] + 0.5;
	info->initial_pos_x = pos[1];
	info->initial_pos_y = pos[0];
	info->player->vision = vision;
	info->map[pos[0]][pos[1]] = '0';
	(*find_player)++;
}

void	ft_find_player_pos(t_info *info)
{
	unsigned int	pos[2];
	unsigned int	find_player;

	find_player = 0;
	pos[0] = 0;
	while (info->map[pos[0]])
	{
		pos[1] = 0;
		while (info->map[pos[0]][pos[1]])
		{
			if (info->map[pos[0]][pos[1]] == 'N')
				ft_set_player_pos(info, pos, &find_player, 0);
			else if (info->map[pos[0]][pos[1]] == 'E')
				ft_set_player_pos(info, pos, &find_player, 90);
			else if (info->map[pos[0]][pos[1]] == 'S')
				ft_set_player_pos(info, pos, &find_player, 180);
			else if (info->map[pos[0]][pos[1]] == 'W')
				ft_set_player_pos(info, pos, &find_player, 270);
			(pos[1])++;
		}
		(pos[0])++;
	}
	if (find_player != 1)
		ft_error_msg("Wrong number of player!\n");
}
