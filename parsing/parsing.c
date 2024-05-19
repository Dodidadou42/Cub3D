/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:04:19 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 16:13:26 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_check_textures_numbers(char *line, unsigned int *line_i, \
unsigned int *nb_elem, int *no_nl)
{
	(*no_nl) = 0;
	if (line != NULL)
		free(line);
	if (line != NULL && line[0] != '\n')
	{
		(*line_i)--;
		(*no_nl) = 1;
	}
	if ((*nb_elem) < 6)
		ft_error_msg("Missing element!\n");
}

void	ft_check_arguments(int argc, char **argv)
{	
	if (argc != 2)
		ft_error_msg("Wrong number of argument!\n");
	if (ft_strrchr_i(argv[1], '.') <= 0)
		ft_error_msg("Wrong map name!\n");
	if (ft_strrchr_i(argv[1], '/') >= 0 && \
	(ft_strrchr_i(argv[1], '.') - ft_strrchr_i(argv[1], '/')) <= 1)
		ft_error_msg("Wrong map name!\n");
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", ft_strlen(argv[1])) != 0)
		ft_error_msg("Wrong map name!\n");
}

t_game	*ft_parsing(int argc, char **argv)
{
	t_game	*game;

	ft_check_arguments(argc, argv);
	game = ft_init_game(argv[1], argv[0]);
	return (game);
}
