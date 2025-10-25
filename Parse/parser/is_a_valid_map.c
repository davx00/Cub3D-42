/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_valid_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:53:22 by despanol          #+#    #+#             */
/*   Updated: 2025/10/15 21:16:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	copy_and_pad_line(char **new, char **map, int y, t_parse *cub3d)
{
	new[y] = malloc(cub3d->map.width + 1);
	if (!new[y])
		return (0);
	ft_strlcpy(new[y], map[y], cub3d->map.width + 1);
	complete_spaces(new[y], ft_strlen(map[y]), cub3d->map.width);
	return (1);
}

char	**make_rectangular_map(char **map, t_parse *cub3d)
{
	int		height;
	char	**new;
	int		y;
	int		current_len;

	height = 0;
	cub3d->map.width = 0;
	while (map[height])
	{
		current_len = ft_strlen(map[height]);
		if (current_len > cub3d->map.width)
			cub3d->map.width = current_len;
		height++;
	}
	new = malloc(sizeof(char *) * (height + 1));
	if (!new)
		return (NULL);
	y = 0;
	while (y < height)
	{
		if (!copy_and_pad_line(new, map, y, cub3d))
			return (free_new_map(new, y), NULL);
		y++;
	}
	return (new[height] = NULL, new);
}

void	character_checker(t_parse *cub3d, char **map_copy, int x, int y)
{
	char	current_char;

	current_char = map_copy[y][x];
	if (current_char != '0' && current_char != '1'
		&& current_char != 'N' && current_char != 'S'
		&& current_char != 'E' && current_char != 'W' && current_char != ' ')
	{
		printf_error(5);
		free_map(map_copy, cub3d);
		free_all(cub3d);
		exit(1);
	}
	validate_border_walls(current_char, x, y, cub3d);
}

static void	find_and_validate_player_position(t_parse *cub3d, char **mp_cpy)
{
	int		x;
	int		y;
	int		player_found;

	player_found = 0;
	y = 0;
	while (mp_cpy[y])
	{
		x = 0;
		while (mp_cpy[y][x])
		{
			if (mp_cpy[y][x] == 'N' || mp_cpy[y][x] == 'S' ||
				mp_cpy[y][x] == 'E' || mp_cpy[y][x] == 'W')
			{
				validate_player_flood_fill(cub3d, mp_cpy, x, y);
				player_found = 1;
				break ;
			}
			x++;
		}
		if (player_found)
			break ;
		y++;
	}
}

void	valid_map(t_parse *cub3d)
{
	int		x;
	int		y;
	char	**mp_cpy;

	cub3d->map.height = 0;
	while (cub3d->map.matriz[cub3d->map.height])
		cub3d->map.height++;
	mp_cpy = make_rectangular_map(cub3d->map.matriz, cub3d);
	if (!mp_cpy)
	{
		printf_error(9);
		free_all(cub3d);
		exit(1);
	}
	y = 0;
	while (mp_cpy[y])
	{
		x = 0;
		while (mp_cpy[y][x])
			character_checker(cub3d, mp_cpy, x++, y);
		y++;
	}
	find_and_validate_player_position(cub3d, mp_cpy);
	free_map(mp_cpy, cub3d);
}
