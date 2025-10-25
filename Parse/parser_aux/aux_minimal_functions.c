/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_minimal_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:32:51 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 16:58:23 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_file_extension(char *file_name)
{
	char	*point;

	point = ft_strrchr(file_name, '.');
	if (point != NULL && ft_strcmp(point, ".cub") == 0)
		return (1);
	else
		return (0);
}

void	complete_spaces(char *line, int i, int width)
{
	while (i < width)
	{
		line[i] = ' ';
		i++;
	}
	line[width] = '\0';
}

int	is_map_line(char *line)
{
	while (*line && *line != '\n')
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W'
			&& *line != 13)
			return (0);
		line++;
	}
	return (1);
}

int	is_line_empty_or_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}
