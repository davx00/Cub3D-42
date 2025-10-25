/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_valid_map_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:04:17 by despanol          #+#    #+#             */
/*   Updated: 2025/10/15 21:33:43 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	flood_fill(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (1);
	map[y][x] = 'x';
	if (!flood_fill(map, x + 1, y, height))
		return (0);
	if (!flood_fill(map, x - 1, y, height))
		return (0);
	if (!flood_fill(map, x, y + 1, height))
		return (0);
	if (!flood_fill(map, x, y - 1, height))
		return (0);
	return (1);
}

void	validate_player_flood_fill(t_parse *cub3d, char **mp_cpy, int x, int y)
{
	char	**flood_copy;

	flood_copy = make_rectangular_map(cub3d->map.matriz, cub3d);
	if (!flood_copy || !flood_fill(flood_copy, x, y, cub3d->map.height))
	{
		printf_error(12);
		if (flood_copy)
			free_map(flood_copy, cub3d);
		free_map(mp_cpy, cub3d);
		free_all(cub3d);
		exit(1);
	}
	free_map(flood_copy, cub3d);
}
