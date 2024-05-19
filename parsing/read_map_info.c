/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <ddychus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:23:58 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 14:05:13 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_analyse_floor(t_info *info, char *line)
{
	if (info->floor_color != -1)
		ft_error_msg("Already init floor color!\n");
	ft_analyse_floor_ceilling(&(info->floor), line);
	info->floor_color = ft_convert_rgb_to_int(info->floor);
}

void	ft_analyse_element(t_info *info, char *line_nl)
{
	char	*line;

	if (ft_strlen(line_nl) < 3)
		ft_error_msg("Wrong element!\n");
	line = ft_strtrim(line_nl, "\n");
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		ft_analyse_dir(&(info->no_texture_name), line);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		ft_analyse_dir(&(info->so_texture_name), line);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		ft_analyse_dir(&(info->ea_texture_name), line);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		ft_analyse_dir(&(info->we_texture_name), line);
	else if (line[0] == 'F' && line[1] == ' ')
		ft_analyse_floor(info, line);
	else if (line[0] == 'C' && line[1] == ' ')
	{	
		if (info->ceiling_color != -1)
			ft_error_msg("Already init ceil color!\n");
		ft_analyse_floor_ceilling(&(info->ceiling), line);
		info->ceiling_color = ft_convert_rgb_to_int(info->ceiling);
	}
	else
		ft_error_msg("Wrong identifier!\n");
	free(line);
}

unsigned int	ft_get_textures_name(t_info *info, int fd, int *no_nl)
{
	char			*line;
	unsigned int	nb_elem;
	unsigned int	line_i;

	nb_elem = 0;
	line_i = 0;
	line = get_next_line(fd);
	while (line != NULL && nb_elem < 6)
	{
		line_i++;
		if (ft_strncmp(line, "\n", ft_strlen(line) != 0))
		{
			ft_analyse_element(info, line);
			nb_elem++;
		}
		free(line);
		line = get_next_line(fd);
	}
	ft_check_textures_numbers(line, &line_i, &nb_elem, no_nl);
	return (line_i);
}

void	ft_fill_map(t_info *info, char *map_name, unsigned int line_i)
{
	unsigned int	i;
	int				fd;
	char			*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Can't open map!\n");
	line = get_next_line(fd);
	i = 0;
	while (i <= line_i)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	i = 0;
	while (line != NULL)
	{
		info->map[i] = ft_strtrim(line, "\n");
		free(line);
		++i;
		line = get_next_line(fd);
	}
	info->map[i] = NULL;
	close(fd);
}

void	ft_read_map_info(t_info *info, char *map_name)
{
	int				fd;
	int				no_nl;
	unsigned int	line_i;
	char			*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Can't open map!\n");
	line_i = ft_get_textures_name(info, fd, &no_nl);
	line = get_next_line(fd);
	while (line != NULL && line[0] == '\n' && no_nl == 0)
	{
		free(line);
		line_i++;
		line = get_next_line(fd);
	}
	info->map_height = no_nl;
	while (line != NULL)
	{
		free(line);
		info->map_height++;
		line = get_next_line(fd);
	}
	info->map = malloc(sizeof(*(info->map)) * (info->map_height + 1));
	ft_fill_map(info, map_name, line_i);
}
