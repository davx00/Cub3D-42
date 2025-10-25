/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:22:21 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 16:58:04 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*read_line_from_file(int fd)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		bytes_read;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	bytes_read = read(fd, buffer, 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (buffer[0] == '\n')
			return (line);
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
		bytes_read = read(fd, buffer, 1);
	}
	if (bytes_read == 0 && ft_strlen(line) > 0)
		return (line);
	return (free(line), NULL);
}

static int	process_map_lines(int fd, t_parse *data, char **map_lines)
{
	char	*line;

	line = read_line_from_file(fd);
	while (line)
	{
		if (parse_map(line, data, map_lines))
			return (free(line), free_map(map_lines, data), close(fd), 0);
		free(line);
		line = read_line_from_file(fd);
	}
	return (1);
}

int	parse(int argc, char **argv, t_parse *data)
{
	int		fd;
	char	**map_lines;

	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 0);
	if (!check_file_extension(argv[1]))
		return (ft_putstr_fd("Error\nInvalid file extension\n", 2), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 0);
	map_lines = malloc(sizeof(char *) * 1000);
	if (!map_lines)
		return (close(fd), 0);
	data->map.index = 0;
	if (!process_map_lines(fd, data, map_lines))
		return (0);
	close(fd);
	map_lines[data->map.index] = NULL;
	data->map.matriz = map_lines;
	find_and_set_player(data);
	valid_map(data);
	return (1);
}
