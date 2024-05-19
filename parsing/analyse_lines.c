/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:29:21 by vdelafos          #+#    #+#             */
/*   Updated: 2023/05/04 09:29:27 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_is_in_range(char	*nb)
{
	int	i;

	i = 0;
	if (nb[0] == '+')
		i++;
	while (nb[i] == '0')
		i++;
	if ((ft_strlen(&(nb[i])) == ft_strlen("255") && \
	ft_strncmp(&(nb[i]), "255", ft_strlen(&(nb[i]))) > 0) || \
	(ft_strlen(&(nb[i])) > ft_strlen("255")))
		return (1);
	return (0);
}

void	ft_analyse_dir(char **name, char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (*name != NULL)
		ft_error_msg("Too much direction!\n");
	*name = ft_strdup(&(line[i]));
}

void	ft_analyse_color(unsigned int *color, char *current_line)
{
	char	*number_chr;
	int		comma_pos;

	comma_pos = ft_strchr_i(current_line, ',');
	if (comma_pos == -1)
		comma_pos = ft_strlen(current_line);
	number_chr = ft_substr(current_line, 0, comma_pos);
	if (!ft_isnum(number_chr))
		ft_error_msg("One element not a number!\n");
	if (number_chr[0] == '-')
		ft_error_msg("One element is negative!\n");
	if (ft_is_in_range(number_chr))
		ft_error_msg("One element is not in range (0, 255)!\n");
	*color = ft_atoi(number_chr);
	free(number_chr);
}

int	ft_nb_occurence(char *str, char chr)
{
	int	nb_occurence;
	int	i;

	nb_occurence = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			nb_occurence++;
		i++;
	}
	return (nb_occurence);
}

void	ft_analyse_floor_ceilling(unsigned int (*color)[3], char *line)
{
	int		i;
	char	*current_line;
	char	*temp_line;

	i = 1;
	while (line[i] == ' ')
		i++;
	current_line = ft_strdup(&(line[i]));
	if (ft_nb_occurence(current_line, ',') != 2)
		ft_error_msg("Wrong format for one color!\n");
	ft_analyse_color(&((*color)[0]), current_line);
	temp_line = current_line;
	current_line = ft_substr(temp_line, ft_strchr_i(current_line, ',') + 1, \
		ft_strlen(current_line) - ft_strchr_i(current_line, ',') - 1);
	free(temp_line);
	ft_analyse_color(&((*color)[1]), current_line);
	temp_line = current_line;
	current_line = ft_substr(temp_line, ft_strchr_i(current_line, ',') + 1, \
		ft_strlen(current_line) - ft_strchr_i(current_line, ',') - 1);
	ft_analyse_color(&((*color)[2]), current_line);
	free(current_line);
	free(temp_line);
}
