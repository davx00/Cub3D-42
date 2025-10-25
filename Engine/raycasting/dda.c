/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:26:52 by despanol          #+#    #+#             */
/*   Updated: 2025/10/17 10:27:06 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	perform_dda_old(t_parse *game, int grid_x, int grid_y)
{
	(void)game;
	(void)grid_x;
	(void)grid_y;
}

void	init_ray_steps(t_parse *game, int grid_x, int grid_y)
{
	(void)grid_x;
	(void)grid_y;
	calculate_step_and_side_dist(game);
}
