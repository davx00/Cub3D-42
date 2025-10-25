/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:47:48 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 17:16:35 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_texture_line(t_parse *cub3d, char *line)
{
	char	*texture_path;
	char	*full_path;

	texture_path = ft_strtrim(line + 3, " \n\t");
	full_path = ft_strjoin("./", texture_path);
	free(texture_path);
	if (!check_file_exists(full_path))
	{
		printf("Error\nTexture file not found: %s\n", full_path);
		free(full_path);
		return (1);
	}
	if (!ft_strncmp(line, "NO", 2) && !cub3d->map.no)
		cub3d->map.no = full_path;
	else if (!ft_strncmp(line, "SO", 2) && !cub3d->map.so)
		cub3d->map.so = full_path;
	else if (!ft_strncmp(line, "WE", 2) && !cub3d->map.we)
		cub3d->map.we = full_path;
	else if (!ft_strncmp(line, "EA", 2) && !cub3d->map.ea)
		cub3d->map.ea = full_path;
	else
		return (printf("Error\nDuplicate texture identifier\n"),
			free(full_path), 1);
	cub3d->map.count_textures++;
	return (0);
}

int	process_texture_config(char *line, t_parse *cub3d)
{
	if ((!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)))
	{
		return (parse_texture_line(cub3d, line));
	}
	return (printf_error(8));
}

int	parse_color_configuration(char *line, t_parse *cub3d)
{
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (validate_rgb_values(line + 1, cub3d->map.rgb_roof))
			return (1);
		cub3d->map.count_rgb++;
		return (0);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (validate_rgb_values(line + 1, cub3d->map.rgb_ground))
			return (1);
		cub3d->map.count_rgb++;
		return (0);
	}
	printf_error(3);
	return (1);
}

int	handle_map_line_content(char *line, t_parse *cub3d, char **map_lines)
{
	if (!is_map_line(line))
	{
		printf_error(6);
		return (1);
	}
	map_lines[cub3d->map.index] = ft_strdup(line);
	cub3d->map.index++;
	return (0);
}
