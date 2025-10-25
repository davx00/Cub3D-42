/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:20 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	update_view_angle(t_parse *game, int keycode)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.03;
	if (keycode == 65363)
		rot_speed = -rot_speed;
	old_dir_x = game->npc.dir_x;
	game->npc.dir_x = game->npc.dir_x * cos(rot_speed)
		- game->npc.dir_y * sin(rot_speed);
	game->npc.dir_y = old_dir_x * sin(rot_speed)
		+ game->npc.dir_y * cos(rot_speed);
	old_plane_x = game->npc.plane_x;
	game->npc.plane_x = game->npc.plane_x * cos(rot_speed)
		- game->npc.plane_y * sin(rot_speed);
	game->npc.plane_y = old_plane_x * sin(rot_speed)
		+ game->npc.plane_y * cos(rot_speed);
}

bool	check_wall(t_parse *game, double x, double y)
{
	int	yi;
	int	xi;

	yi = (int)y;
	xi = (int)x;
	if (yi < 0 || yi >= game->map.height || xi < 0 || xi >= game->map.width)
		return (true);
	if (xi >= (int)ft_strlen(game->map.matriz[yi]))
		return (true);
	return (game->map.matriz[yi][xi] == '1');
}

int	process_player_actions(t_parse *game)
{
	if (game->npc.movement.right)
		update_view_angle(game, 65361);
	if (game->npc.movement.left)
		update_view_angle(game, 65363);
	move_npc(game);
	fill_image_buffer(game, 0x000000);
	draw_ceiling_and_floor(game);
	render_scene(game);
	return (0);
}

int	key_down(int key, t_parse *game)
{
	if (key == 119 || key == 'w')
		game->npc.movement.w = true;
	else if (key == 115 || key == 's')
		game->npc.movement.s = true;
	else if (key == 97 || key == 'a')
		game->npc.movement.a = true;
	else if (key == 100 || key == 'd')
		game->npc.movement.d = true;
	else if (key == 65361)
		game->npc.movement.left = true;
	else if (key == 65363)
		game->npc.movement.right = true;
	else if (key == 65307)
		close_window(game);
	return (0);
}

int	key_up(int key, t_parse *game)
{
	if (key == 119 || key == 'w')
		game->npc.movement.w = false;
	else if (key == 115 || key == 's')
		game->npc.movement.s = false;
	else if (key == 97 || key == 'a')
		game->npc.movement.a = false;
	else if (key == 100 || key == 'd')
		game->npc.movement.d = false;
	else if (key == 65361)
		game->npc.movement.left = false;
	else if (key == 65363)
		game->npc.movement.right = false;
	return (0);
}
