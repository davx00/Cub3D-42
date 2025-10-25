/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:49:27 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	free_all(t_parse *cub3d)
{
	free_paths(cub3d);
	free_matriz_map(cub3d);
	free_new_matriz(cub3d);
	if (cub3d->mlx_ptr)
		free_mlx_images(cub3d);
	return (0);
}

int	close_window(t_parse *cub3d)
{
	if (cub3d->win_ptr && cub3d->mlx_ptr)
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	free_all(cub3d);
	exit(0);
	return (0);
}

void	free_mlx_images(t_parse *cub3d)
{
	if (cub3d->image.north.img_text)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.north.img_text);
	if (cub3d->image.south.img_text)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.south.img_text);
	if (cub3d->image.east.img_text)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.east.img_text);
	if (cub3d->image.west.img_text)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.west.img_text);
	if (cub3d->image.img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->image.img);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
	}
	else
		return ;
}
