/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:54:05 by ddychus           #+#    #+#             */
/*   Updated: 2023/05/03 15:07:49 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_init_ray(t_game *game, float vision)
{
	game->ray_x->delta_diag_dist = ft_get_delta_dist_x(vision);
	game->ray_y->delta_diag_dist = ft_get_delta_dist_y(vision);
	game->ray_x->pos_x = game->player->pos_x;
	game->ray_x->pos_y = game->player->pos_y;
	game->ray_y->pos_x = game->player->pos_x;
	game->ray_y->pos_y = game->player->pos_y;
	game->ray_x->side_diag_dist
		= ft_get_side_dist_x(game->ray_x->pos_y, vision);
	game->ray_y->side_diag_dist
		= ft_get_side_dist_y(game->ray_y->pos_x, vision);
	ft_get_ray_dist_x(game->ray_x, vision);
	ft_get_ray_dist_y(game->ray_y, vision);
	game->ray_x->traveled_dist = 0;
	game->ray_y->traveled_dist = 0;
	game->ray_x->i = 0;
	game->ray_y->i = 0;
}

void	ft_update_dist(float *dist_x, float *dist_y, t_game *game)
{
	if (!game->ray_x->i)
		*dist_x = game->ray_x->side_diag_dist;
	else
		*dist_x = game->ray_x->delta_diag_dist;
	if (!game->ray_y->i)
		*dist_y = game->ray_y->side_diag_dist;
	else
		*dist_y = game->ray_y->delta_diag_dist;
}

void	ft_cast_next_point_x(t_ray *ray, float vision)
{
	if (!ray->i)
	{
		if (0 <= vision && vision <= 180)
			ray->pos_x += ray->side_line_dist;
		else
			ray->pos_x -= ray->side_line_dist;
		ray->traveled_dist += ray->side_diag_dist;
		if (90 <= vision && vision <= 270)
			ray->pos_y = ceil(ray->pos_y);
		else
			ray->pos_y = floor(ray->pos_y);
		ray->i++;
	}
	else
	{
		if (0 <= vision && vision <= 180)
			ray->pos_x += ray->delta_line_dist;
		else
			ray->pos_x -= ray->delta_line_dist;
		ray->traveled_dist += ray->delta_diag_dist;
		if (90 <= vision && vision <= 270)
			ray->pos_y++;
		else
			ray->pos_y--;
	}
}

void	ft_cast_next_point_y(t_ray *ray, float vision)
{
	if (!ray->i)
	{
		if (90 <= vision && vision <= 270)
			ray->pos_y += ray->side_line_dist;
		else
			ray->pos_y -= ray->side_line_dist;
		ray->traveled_dist += ray->side_diag_dist;
		if (0 <= vision && vision <= 180)
			ray->pos_x = ceil(ray->pos_x);
		else
			ray->pos_x = floor(ray->pos_x);
		ray->i++;
	}
	else
	{
		if (90 <= vision && vision <= 270)
			ray->pos_y += ray->delta_line_dist;
		else
			ray->pos_y -= ray->delta_line_dist;
		ray->traveled_dist += ray->delta_diag_dist;
		if (0 <= vision && vision <= 180)
			ray->pos_x++;
		else
			ray->pos_x--;
	}
}

void	ft_cast_ray(t_game *game, float vision, int i_pixel)
{
	float	dist_x;
	float	dist_y;
	int		i;

	i = 0;
	ft_init_ray(game, vision);
	while (1)
	{
		ft_update_dist(&dist_x, &dist_y, game);
		if (game->ray_x->traveled_dist + dist_x
			<= game->ray_y->traveled_dist + dist_y)
		{
			ft_cast_next_point_x(game->ray_x, vision);
			if (!ft_check_wall_x(game, vision, i_pixel))
				break ;
		}
		else
		{
			ft_cast_next_point_y(game->ray_y, vision);
			if (!ft_check_wall_y(game, vision, i_pixel))
				break ;
		}
		i++;
	}
}
