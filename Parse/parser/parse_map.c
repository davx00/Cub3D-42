/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:51:44 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 16:35:57 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_and_handle_map_start(char *line, t_parse *cub3d,
				char **map_lines)
{
	if (cub3d->map.count_textures != 4 || cub3d->map.count_rgb != 2)
	{
		printf("Error\nMissing identifiers before map\n");
		return (1);
	}
	cub3d->map.parse = 2;
	cub3d->map.index = 0;
	return (handle_map_line_content(line, cub3d, map_lines));
}

int	parse_map(char *line, t_parse *cub3d, char **map_lines)
{
	if (cub3d->map.parse == 2)
	{
		if (is_line_empty_or_whitespace(line))
		{
			printf("Error\nEmpty line inside map\n");
			return (1);
		}
		return (handle_map_line_content(line, cub3d, map_lines));
	}
	if (is_line_empty_or_whitespace(line))
		return (0);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (process_texture_config(line, cub3d));
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (parse_color_configuration(line, cub3d));
	if (is_map_line(line))
		return (validate_and_handle_map_start(line, cub3d, map_lines));
	printf("Error\nUnexpected line\n");
	return (1);
}
