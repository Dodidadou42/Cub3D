/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_dist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:29:01 by vdelafos          #+#    #+#             */
/*   Updated: 2023/04/25 16:49:08 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_get_ray_dist_x(t_ray *ray_info, float vision)
{
	float	dist_to_line_y;

	if (270 <= vision || vision <= 90)
		dist_to_line_y = ray_info->pos_y - floor(ray_info->pos_y);
	else
		dist_to_line_y = ceil(ray_info->pos_y) - ray_info->pos_y;
	ray_info->side_line_dist = \
	sqrt(fabs(pow(ray_info->side_diag_dist, 2) - pow(dist_to_line_y, 2)));
	ray_info->delta_line_dist = \
	sqrt(fabs(pow(ray_info->delta_diag_dist, 2) - 1));
}

void	ft_get_ray_dist_y(t_ray *ray_info, float vision)
{
	float	dist_to_line_x;

	if (0 <= vision && vision <= 180)
		dist_to_line_x = fabs(ceil(ray_info->pos_x) - ray_info->pos_x);
	else
		dist_to_line_x = fabs(ray_info->pos_x - floor(ray_info->pos_x));
	ray_info->side_line_dist = \
	sqrt(pow(ray_info->side_diag_dist, 2) - pow(dist_to_line_x, 2));
	ray_info->delta_line_dist = \
	sqrt(pow(ray_info->delta_diag_dist, 2) - 1);
}
