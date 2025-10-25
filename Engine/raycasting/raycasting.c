/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:27:46 by despanol          #+#    #+#             */
/*   Updated: 2025/10/17 10:30:51 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_ray(t_parse *game, int x)
{
	game->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray.ray_dir_x = game->npc.dir_x
		+ game->npc.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = game->npc.dir_y
		+ game->npc.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->npc.x;
	game->ray.map_y = (int)game->npc.y;
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_x = 1e30;
	else
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = 1e30;
	else
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	game->ray.hit = 0;
}

void	calculate_step_and_side_dist(t_parse *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->npc.x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->npc.x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->npc.y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->npc.y)
			* game->ray.delta_dist_y;
	}
}

static void	perform_dda(t_parse *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->ray.map_x < 0 || game->ray.map_x >= game->map.width
			|| game->ray.map_y < 0 || game->ray.map_y >= game->map.height)
			break ;
		if (game->map.matriz[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.hit = 1;
	}
}

static void	calculate_wall_distance(t_parse *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->npc.x
				+ (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->npc.y
				+ (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
	if (game->ray.perp_wall_dist < 0.01)
		game->ray.perp_wall_dist = 0.01;
}

void	render_scene(t_parse *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, x);
		calculate_step_and_side_dist(game);
		perform_dda(game);
		calculate_wall_distance(game);
		render_wall_slice(game, x);
		x++;
	}
	render_buffer_to_window(game);
}
