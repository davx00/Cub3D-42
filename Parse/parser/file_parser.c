/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:44:30 by despanol          #+#    #+#             */
/*   Updated: 2025/10/15 18:21:35 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_rgb_values(char *color_str, int rgb[3])
{
	char	**color_components;
	int		component_index;
	char	*trimmed;

	trimmed = ft_strtrim(color_str, " \t\n");
	color_components = ft_split(trimmed, ',');
	free(trimmed);
	if (!color_components || !color_components[0]
		|| !color_components[1] || !color_components[2])
	{
		printf_error_rgb(color_components, NULL);
		return (1);
	}
	component_index = 0;
	while (component_index < 3)
	{
		if (process_rgb_component(color_components, component_index,
				&rgb[component_index]))
			return (1);
		component_index++;
	}
	free_str(color_components);
	return (0);
}
