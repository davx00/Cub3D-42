/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:29:43 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 17:49:47 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	printf_error_rgb(char **color, char *clean)
{
	if (clean)
		free(clean);
	if (color)
		free_str(color);
	printf_error(1);
	return (1);
}

int	process_rgb_component(char **color, int i, int *rgb)
{
	char	*clean;
	int		j;

	clean = ft_strtrim(color[i], " \t\n");
	if (!clean || *clean == '\0')
		return (printf_error_rgb(color, clean));
	j = -1;
	while (clean[++j])
		if (!ft_isdigit(clean[j]) && clean[j] != 13)
			return (printf_error_rgb(color, clean));
	*rgb = ft_atoi(clean);
	if (*rgb < 0 || *rgb > 255)
		return (printf_error_rgb(color, clean));
	free(clean);
	return (0);
}
