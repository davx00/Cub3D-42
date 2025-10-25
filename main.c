/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:00:16 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 17:01:20 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	main(int argc, char **argv)
{
	t_parse	game;
	int		parse_result;

	ft_bzero(&game, sizeof(t_parse));
	parse_result = parse(argc, argv, &game);
	if (parse_result != 1)
	{
		free_all(&game);
		return (1);
	}
	main_engine(&game);
	free_all(&game);
	return (0);
}
