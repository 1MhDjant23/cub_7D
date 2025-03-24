/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:51:57 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/23 16:48:21 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	err(char *str)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
	return (1);
}

void	complex_err(t_cub *data, char *str, char *i, char *j)
{
	err("Error\nline `");
	err(i);
	err("', Col `");
	err(j);
	err("'; ");
	err(str);
	err("\n");
	free(i);
	i = NULL;
	free(j);
	j = NULL;
	free_map_ele(data->maps);
	exit(EXIT_FAILURE);
}

void	simple_err(t_cub *data, char *str)
{
	(void)data;
	err("Error\n");
	err(str);
	free_struct(data);
	exit(1);
}

void	print_err(t_stat stat)
{
	write(2, "Error\n", 6);
	if (stat == EXTENS)
		write(2, "Invalid file (extension file must end with `.cub`)\n", 51);
	if (stat == EMPTY)
		write(2, "empty file!! (please enter a valid map and retry.)\n", 51);
}

int	err_or(t_cub *data, char *str, char *index, int stat)
{
	(void)data;
	write(2, "Error\n(line: ` ", 15);
	write(2, index, ft_strlen(index));
	write(2, "')", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(index);
	index = NULL;
	if (stat == 0)
		free_struct(data);
	exit(STDERR_FILENO);
}
