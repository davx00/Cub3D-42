/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:29:47 by despanol          #+#    #+#             */
/*   Updated: 2025/10/21 16:06:42 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	printf_error(int error)
{
	if (error == 1)
		printf("Error\n");
	else if (error == 2)
		printf("Error\n No valid map, free lines");
	else if (error == 3)
		printf("Error\n Expected color");
	else if (error == 4)
		printf("Error\n No valid map, map borders must be walls");
	else if (error == 5)
		printf("Error\n No valid map, invalid character in map");
	else if (error == 6)
		printf("Error\n Unexpected line after map");
	else if (error == 7)
		printf("Error\n number of player no correct");
	else if (error == 8)
		printf("Error\n Expected texture line");
	else if (error == 9)
		printf("Error\n Failed allocating map memory");
	else if (error == 10)
		printf("Error\n no file founded");
	else if (error == 11)
		printf("Error\n The Extension is not correct");
	else if (error == 12)
		printf("Error\n Invalid map, not closed");
	return (0);
}
