/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:39:56 by despanol          #+#    #+#             */
/*   Updated: 2025/10/17 10:23:24 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	*select_texture(t_parse *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			return (&game->image.east);
		else
			return (&game->image.west);
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			return (&game->image.south);
		else
			return (&game->image.north);
	}
}

double	calc_wall_x(t_parse *game)
{
	double	result;

	if (game->ray.side == 0)
		result = game->npc.y
			+ game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		result = game->npc.x
			+ game->ray.perp_wall_dist * game->ray.ray_dir_x;
	result -= floor(result);
	return (result);
}

int	calc_tex_x(t_parse *game, t_texture *texture, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if ((game->ray.side == 0 && game->ray.ray_dir_x > 0)
		|| (game->ray.side == 1 && game->ray.ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	calc_tex_y(t_parse *game, t_texture *texture, int draw_start, int y)
{
	int		line_height;
	double	step;
	double	tex_pos;
	int		tex_y;

	line_height = (int)(SCREEN_HEIGHT / game->ray.perp_wall_dist);
	step = (double)texture->heght / line_height;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	tex_y = (int)tex_pos + (int)((y - draw_start) * step);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->heght)
		tex_y = texture->heght - 1;
	return (tex_y);
}

unsigned int	get_tex_color(t_texture *texture, int tex_x,
			int tex_y, int side)
{
	unsigned int	color;

	if (texture->data)
		color = *(unsigned int *)(texture->data
				+ (tex_y * texture->length
					+ tex_x * (texture->pixel / 8)));
	else
		color = 0xFF00FF;
	if (side == 1)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}
