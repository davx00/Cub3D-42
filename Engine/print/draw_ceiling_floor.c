/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:07 by despanol          #+#    #+#             */
/*   Updated: 2025/10/17 10:21:39 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fill_background_strip(t_parse *game, int y_start,
	int y_end, int color)
{
	int	*pixel_buffer;
	int	row;
	int	col;
	int	index;

	pixel_buffer = (int *)game->image.data;
	row = y_start;
	while (row < y_end)
	{
		col = 0;
		while (col < SCREEN_WIDTH)
		{
			index = row * SCREEN_WIDTH + col;
			pixel_buffer[index] = color;
			col++;
		}
		row++;
	}
}

static int	rgb_to_hex(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | (rgb[2]));
}

void	draw_ceiling_and_floor(t_parse *game)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_hex(game->map.rgb_roof);
	floor_color = rgb_to_hex(game->map.rgb_ground);
	fill_background_strip(game, 0, SCREEN_HEIGHT / 2, ceiling_color);
	fill_background_strip(game, SCREEN_HEIGHT / 2, SCREEN_HEIGHT, floor_color);
}
