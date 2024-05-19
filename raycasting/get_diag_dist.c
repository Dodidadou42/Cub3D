/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diag_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:48 by vdelafos          #+#    #+#             */
/*   Updated: 2023/04/25 16:49:35 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

float	ft_get_side_dist_x(float pos_y, float vision)
{
	float	side_dist_x;
	float	dist_to_line_y;
	float	angle_rad;

	if (270 <= vision || vision <= 90)
	{
		dist_to_line_y = pos_y - floor(pos_y);
		if (0 <= vision && vision <= 180)
			angle_rad = cos(vision * M_PI / 180);
		else
			angle_rad = cos((360 - vision) * M_PI / 180);
	}
	else
	{
		dist_to_line_y = ceil(pos_y) - pos_y;
		if (0 <= vision && vision <= 180)
			angle_rad = cos((180 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 180) * M_PI / 180);
	}
	side_dist_x = dist_to_line_y / angle_rad;
	return (side_dist_x);
}

float	ft_get_side_dist_y(float pos_x, float vision)
{
	float	side_dist_y;
	float	dist_to_line_x;
	float	angle_rad;

	if (0 <= vision && vision <= 180)
	{
		dist_to_line_x = fabs(ceil(pos_x) - pos_x);
		if (270 <= vision || vision <= 90)
			angle_rad = cos((90 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 90) * M_PI / 180);
	}
	else
	{
		dist_to_line_x = fabs(pos_x - floor(pos_x));
		if (270 <= vision || vision <= 90)
			angle_rad = cos((270 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 270) * M_PI / 180);
	}
	side_dist_y = dist_to_line_x / angle_rad;
	return (side_dist_y);
}

float	ft_get_delta_dist_x(float vision)
{
	float	delta_dist_x;
	float	angle_rad;

	if (270 <= vision || vision <= 90)
	{
		if (0 <= vision && vision <= 180)
			angle_rad = cos(vision * M_PI / 180);
		else
			angle_rad = cos((360 - vision) * M_PI / 180);
	}
	else
	{
		if (0 <= vision && vision <= 180)
			angle_rad = cos((180 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 180) * M_PI / 180);
	}
	delta_dist_x = 1 / angle_rad;
	return (delta_dist_x);
}

float	ft_get_delta_dist_y(float vision)
{
	float	delta_dist_y;
	float	angle_rad;

	if (0 <= vision && vision <= 180)
	{
		if (270 <= vision || vision <= 90)
			angle_rad = cos((90 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 90) * M_PI / 180);
	}
	else
	{
		if (270 <= vision || vision <= 90)
			angle_rad = cos((270 - vision) * M_PI / 180);
		else
			angle_rad = cos((vision - 270) * M_PI / 180);
	}
	delta_dist_y = 1 / angle_rad;
	return (delta_dist_y);
}
