/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_valid_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:31:43 by despanol          #+#    #+#             */
/*   Updated: 2025/10/15 21:32:29 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_border_walls(char current_char, int x, int y, t_parse *cub3d)
{
	int	width;
	int	height;

	width = cub3d->map.width;
	height = cub3d->map.height;
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
	{
		if (current_char != '1' && current_char != ' ')
		{
			printf_error(4);
			free_all(cub3d);
			exit(1);
		}
	}
}

int	needs_flood_fill_validation(char current_char)
{
	if (current_char != '0' && current_char != '1'
		&& current_char != 'N' && current_char != 'S'
		&& current_char != 'E' && current_char != 'W')
	{
		return (0);
	}
	return (1);
}

void	validate_flood_fill(t_parse *cub3d, char **map_copy,
	char **rectangular_map, int coords[2])
{
	int	map_height;
	int	x;
	int	y;

	map_height = cub3d->map.height;
	x = coords[0];
	y = coords[1];
	if (!flood_fill(rectangular_map, x, y, map_height))
	{
		printf_error(12);
		free_map(rectangular_map, cub3d);
		free_map(map_copy, cub3d);
		free_all(cub3d);
		exit(1);
	}
	if (cub3d->map.matriz_new)
		free_map(cub3d->map.matriz_new, cub3d);
	cub3d->map.matriz_new = rectangular_map;
}
