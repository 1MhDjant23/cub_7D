/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:35:59 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/24 17:47:32 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_compare(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void	init_data(t_cub *data)
{
	data->file = NULL;
	data->map = NULL;
	data->line_m = NULL;
	data->help = NULL;
	data->begin_map = 0;
	data->count_elem = 0;
	data->end_map = 0;
	data->player = 0;
}

void	init_data_2(t_help *help, t_map *maps, t_stat stat)
{
	if (stat == HELP)
	{
		help->i = 0;
		help->x = 0;
		help->tmp = NULL;
		help->player = 0;
		help->C = false;
		help->F = false;
		help->NO = false;
		help->SO = false;
		help->WE = false;
		help->EA = false;
		return ;
	}
	maps->map = NULL;
	maps->CE_color = 0;
	maps->FL_color = 0;
	maps->N_texture = NULL;
	maps->W_texture = NULL;
	maps->S_texture = NULL;
	maps->E_texture = NULL;
	maps->pl_xx = 0;
	maps->pl_yy = 0;
	maps->rwo = 0;
	maps->column = 0;
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	coun_line(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}
