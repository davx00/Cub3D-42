/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:04 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	load_single_texture(t_parse *game,
	t_texture *texture, char *file_path)
{
	texture->img_text = mlx_xpm_file_to_image(game->mlx_ptr, file_path,
			&texture->width, &texture->heght);
	if (texture->img_text != NULL)
	{
		texture->data = mlx_get_data_addr(texture->img_text,
				&texture->pixel, &texture->length, &texture->endian);
		printf("[TEXTURE] Loaded: %s (%dx%d)\n", file_path,
			texture->width, texture->heght);
	}
	else
	{
		texture->data = NULL;
		printf("[ERROR] Failed to load texture: %s\n", file_path);
	}
}

void	initialize_image_and_textures(t_parse *game)
{
	int			i;
	char		*tex_paths[4];
	t_texture	*tex_targets[4];

	tex_paths[0] = game->map.no;
	tex_paths[1] = game->map.so;
	tex_paths[2] = game->map.ea;
	tex_paths[3] = game->map.we;
	tex_targets[0] = &game->image.north;
	tex_targets[1] = &game->image.south;
	tex_targets[2] = &game->image.east;
	tex_targets[3] = &game->image.west;
	game->image.img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->image.data = mlx_get_data_addr(game->image.img,
			&game->image.pixel, &game->image.length, &game->image.endian);
	i = 0;
	while (i < 4)
	{
		load_single_texture(game, tex_targets[i], tex_paths[i]);
		i++;
	}
}
