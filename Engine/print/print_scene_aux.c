/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:17:43 by despanol          #+#    #+#             */
/*   Updated: 2025/10/17 12:24:20 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	*get_wall_texture(t_parse *game)
{
	t_texture	*texture;

	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			texture = &game->image.east;
		else
			texture = &game->image.west;
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			texture = &game->image.south;
		else
			texture = &game->image.north;
	}
	return (texture);
}

int	calculate_tex_x(t_parse *game, t_texture *texture)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->npc.y + game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		wall_x = game->npc.x + game->ray.perp_wall_dist * game->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	calculate_tex_y(t_texture *texture, int draw_start, int y,
		double perp_wall_dist)
{
	int		line_height;
	double	step;
	int		tex_y;

	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	step = 1.0 * texture->heght / line_height;
	tex_y = (int)((draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step);
	tex_y += (int)((y - draw_start) * step);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->heght)
		tex_y = texture->heght - 1;
	return (tex_y);
}

void	render_buffer_to_window(t_parse *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->image.img, 0, 0);
}
