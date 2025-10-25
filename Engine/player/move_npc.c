/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:45 by despanol          #+#    #+#             */
/*   Updated: 2025/10/18 10:01:15 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	advance_forward(t_parse *game, double speed, double pad)
{
	double	next_x;
	double	next_y;
	double	curr_x;
	double	curr_y;

	curr_x = game->npc.x;
	curr_y = game->npc.y;
	next_x = curr_x + game->npc.dir_x * speed;
	next_y = curr_y + game->npc.dir_y * speed;
	if (!check_wall(game, next_x + game->npc.dir_x * pad, curr_y))
		game->npc.x = next_x;
	if (!check_wall(game, curr_x, next_y + game->npc.dir_y * pad))
		game->npc.y = next_y;
}

static void	go_backward(t_parse *game, double speed, double pad)
{
	double	prev_x;
	double	prev_y;
	double	curr_x;
	double	curr_y;

	curr_x = game->npc.x;
	curr_y = game->npc.y;
	prev_x = curr_x - game->npc.dir_x * speed;
	prev_y = curr_y - game->npc.dir_y * speed;
	if (!check_wall(game, prev_x - game->npc.dir_x * pad, curr_y))
		game->npc.x = prev_x;
	if (!check_wall(game, curr_x, prev_y - game->npc.dir_y * pad))
		game->npc.y = prev_y;
}

static void	step_left(t_parse *game, double speed, double pad)
{
	double	new_x;
	double	new_y;
	double	curr_x;
	double	curr_y;

	curr_x = game->npc.x;
	curr_y = game->npc.y;
	new_x = curr_x - game->npc.dir_y * speed;
	new_y = curr_y + game->npc.dir_x * speed;
	if (!check_wall(game, new_x - game->npc.dir_y * pad, curr_y))
		game->npc.x = new_x;
	if (!check_wall(game, curr_x, new_y + game->npc.dir_x * pad))
		game->npc.y = new_y;
}

static void	step_right(t_parse *game, double speed, double pad)
{
	double	new_x;
	double	new_y;
	double	curr_x;
	double	curr_y;

	curr_x = game->npc.x;
	curr_y = game->npc.y;
	new_x = curr_x + game->npc.dir_y * speed;
	new_y = curr_y - game->npc.dir_x * speed;
	if (!check_wall(game, new_x + game->npc.dir_y * pad, curr_y))
		game->npc.x = new_x;
	if (!check_wall(game, curr_x, new_y - game->npc.dir_x * pad))
		game->npc.y = new_y;
}

void	move_npc(t_parse *game)
{
	double	speed;
	double	pad;

	speed = 0.06;
	pad = 0.001;
	if (game->npc.movement.w)
		advance_forward(game, speed, pad);
	if (game->npc.movement.s)
		go_backward(game, speed, pad);
	if (game->npc.movement.a)
		step_right(game, speed, pad);
	if (game->npc.movement.d)
		step_left(game, speed, pad);
}
