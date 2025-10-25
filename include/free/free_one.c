/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:44:39 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 16:23:34 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_new_map(char **map, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(char **map_lines, t_parse *cub3d)
{
	int	i;

	i = 0;
	if (!map_lines)
		return ;
	while (i < cub3d->map.index)
	{
		if (map_lines[i] != NULL)
		{
			free(map_lines[i]);
			map_lines[i] = NULL;
		}
		i++;
	}
	free(map_lines);
	map_lines = NULL;
}

void	free_paths(t_parse *cub3d)
{
	if (cub3d->map.no)
		free(cub3d->map.no);
	if (cub3d->map.so)
		free(cub3d->map.so);
	if (cub3d->map.we)
		free(cub3d->map.we);
	if (cub3d->map.ea)
		free(cub3d->map.ea);
}

void	free_matriz_map(t_parse *cub3d)
{
	int	i;

	if (cub3d->map.matriz)
	{
		i = 0;
		while (cub3d->map.matriz[i])
		{
			free(cub3d->map.matriz[i]);
			i++;
		}
		free(cub3d->map.matriz);
	}
}

void	free_new_matriz(t_parse *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d->map.matriz_new)
		return ;
	while (cub3d->map.matriz_new[i] != NULL)
	{
		free(cub3d->map.matriz_new[i]);
		i++;
	}
	free(cub3d->map.matriz_new);
	cub3d->map.matriz = NULL;
}
