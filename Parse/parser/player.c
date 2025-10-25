/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:35:25 by despanol          #+#    #+#             */
/*   Updated: 2025/10/15 21:26:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	validate_player_count_is_one(t_parse *cub3d)
{
	if (cub3d->npc.count != 1)
	{
		printf_error(7);
		free_all(cub3d);
		exit(1);
	}
}

void	init_player_position(t_parse *cub3d, int x, int y, char direction)
{
	cub3d->npc.x = (double) x + 0.5;
	cub3d->npc.y = (double) y + 0.5;
	cub3d->npc.direct = direction;
	if (direction == 'E')
		cub3d->npc.angle = 0.00;
	else if (direction == 'N')
		cub3d->npc.angle = 90.00;
	else if (direction == 'W')
		cub3d->npc.angle = 180.00;
	else if (direction == 'S')
		cub3d->npc.angle = 270.00;
}

void	find_and_set_player(t_parse *cub3d)
{
	int		x;
	int		y;
	char	current_char;

	y = 0;
	while (cub3d->map.matriz[y])
	{
		x = 0;
		while (cub3d->map.matriz[y][x])
		{
			current_char = cub3d->map.matriz[y][x];
			if (current_char == 'N' || current_char == 'S'
				|| current_char == 'E' || current_char == 'W')
			{
				init_player_position(cub3d, x, y, current_char);
				cub3d->npc.count++;
			}
			x++;
		}
		y++;
	}
	validate_player_count_is_one(cub3d);
}
