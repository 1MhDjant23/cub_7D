/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:51:57 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:33 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	err(char *str)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
	return (1);
}

void	print_err(t_stat stat)
{
	write(2, "Error\n", 6);
	if (stat == EXTENS)
		write(2, "Invalid file (extension file must end with `.cub`)\n", 51);
	if (stat == EMPTY)
		write(2, "empty file!! (please enter a valid map and retry.)\n", 51);
}

int	print_errline(char *i_to_a, char *s1)
{
	int	i;

	i = 4;
	if (s1)
	{
		write(2, s1, ft_strlen(s1));
		i = 3;
	}
	write(2, "(line: `", 8);
	write(2, i_to_a, ft_strlen(i_to_a));
	write(2, "').\n", i);
	free(i_to_a);
	i_to_a = NULL;
	return (1);
}

void	cannot_find(char *str)
{
	if (ft_compare(str, "NO ") == 0)
		write(2, "Error\nEnter valid path to the `NORTH` tetxure.\n", 47);
	if (ft_compare(str, "SO ") == 0)
		write(2, "Error\nEnter valid path to the `SOUTH` tetxure.\n", 47);
	if (ft_compare(str, "WE ") == 0)
		write(2, "Error\nEnter valid path to the `WEST` texture.\n", 47);
	if (ft_compare(str, "EA ") == 0)
		write(2, "Error\nEnter valid path to the `EAST` texture.\n", 47);
	if (ft_compare(str, "F ") == 0)
		write(2, "Error\n`FLOOR COLOR`Set R,G,B colors in range [0,255].\n",54);
	if (ft_compare(str, "C ") == 0)
		write(2, "Error\n`CEILING COLOR`Set R,G,B colors in range [0,255].\n", 56);
}

void	elem_not_found(char *str)
{
	if (ft_compare(str, "NO ") == 0)
		write(2, "Error\nObject `NO` not found, please enter `NO`", 46);
	if (ft_compare(str, "SO ") == 0)
		write(2, "Error\nObject `SO` not found, please enter `SO`", 46);
	if (ft_compare(str, "WE ") == 0)
		write(2, "Error\nObject `WE` not found, please enter `WE`", 46);
	if (ft_compare(str, "EA ") == 0)
		write(2, "Error\nObject `EA` not found, please enter `EA`", 46);
	if (ft_compare(str, "F ") == 0)
		write(2, "Error\nObject `F` FLOOR COLOR not found, please enter `F`", 56);
	if (ft_compare(str, "C ") == 0)
		write(2, "Error\nObject `C`CEILING COLOR not found, please enter `C`", 57);
	write(2, " followed by it's path.\n", 24);
}
