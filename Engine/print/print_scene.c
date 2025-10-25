/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:39:56 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_image_buffer(t_parse *game, int color)
{
	int	*buffer;
	int	total_pixels;
	int	i;

	buffer = (int *)game->image.data;
	total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
	i = 0;
	while (i < total_pixels)
	{
		buffer[i] = color;
		i++;
	}
}

static unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	unsigned int	color;

	if (!texture || !texture->data)
		return (0xFF00FF);
	if (tex_x < 0 || tex_x >= texture->width)
		tex_x = 0;
	if (tex_y < 0 || tex_y >= texture->heght)
		tex_y = 0;
	color = *(unsigned int *)(texture->data + (tex_y * texture->length
				+ tex_x * (texture->pixel / 8)));
	return (color);
}

static unsigned int	draw_texture_column(t_parse *game,
		int draw_start, int y)
{
	t_texture		*texture;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	texture = get_wall_texture(game);
	tex_x = calculate_tex_x(game, texture);
	tex_y = calculate_tex_y(texture, draw_start, y, game->ray.perp_wall_dist);
	color = get_texture_color(texture, tex_x, tex_y);
	if (game->ray.side == 1)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

void	draw_wall_column(t_parse *game, int draw_start, int draw_end, int x)
{
	unsigned int	wall_color;
	int				y;
	int				*buffer;

	y = draw_start;
	while (y < draw_end)
	{
		wall_color = draw_texture_column(game, draw_start, y);
		if (y >= 0 && y < SCREEN_HEIGHT)
		{
			buffer = (int *)game->image.data;
			buffer[y * SCREEN_WIDTH + x] = (int)wall_color;
		}
		y++;
	}
}

void	render_wall_slice(t_parse *game, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;

	if (game->ray.hit == 0)
		return ;
	line_height = (int)(SCREEN_HEIGHT / game->ray.perp_wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	draw_wall_column(game, draw_start, draw_end, x);
}
