/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:32:16 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_direction_west(t_parse *game)
{
	game->npc.dir_x = -1;
	game->npc.dir_y = 0;
	game->npc.plane_x = 0;
	game->npc.plane_y = -0.66;
}

static void	set_player_direction(t_parse *game, char initial_dir)
{
	if (initial_dir == 'N')
	{
		game->npc.dir_x = 0;
		game->npc.dir_y = -1;
		game->npc.plane_x = 0.66;
		game->npc.plane_y = 0;
	}
	else if (initial_dir == 'E')
	{
		game->npc.dir_x = 1;
		game->npc.dir_y = 0;
		game->npc.plane_x = 0;
		game->npc.plane_y = 0.66;
	}
	else if (initial_dir == 'S')
	{
		game->npc.dir_x = 0;
		game->npc.dir_y = 1;
		game->npc.plane_x = -0.66;
		game->npc.plane_y = 0;
	}
	else if (initial_dir == 'W')
		set_direction_west(game);
	else
		printf("Direction Error\n");
}

void	main_engine(t_parse *ctx)
{
	set_player_direction(ctx, ctx->npc.direct);
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	initialize_image_and_textures(ctx);
	mlx_hook(ctx->win_ptr, 2, 1L << 0, key_down, ctx);
	mlx_hook(ctx->win_ptr, 3, 1L << 1, key_up, ctx);
	mlx_hook(ctx->win_ptr, 17, 0, close_window, ctx);
	mlx_loop_hook(ctx->mlx_ptr, process_player_actions, ctx);
	mlx_loop(ctx->mlx_ptr);
}
