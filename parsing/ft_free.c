/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:51:00 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 17:58:38 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	free_struct(t_cub *data)
{
	while (data->filling)
	{
		free(data->filling->line);
		data->filling->line = NULL;
		free(data->filling);
		data->filling = NULL;
		data->filling = data->filling->next;
	}
	free(data->filling);
	data->filling = NULL;
	return (1);
}

void	free_d_arr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int	free_all_data(t_cub *data)
{
	free_struct(data);
	free_map_ele(data->maps);
	return (1);
}

void	free_map_ele(t_map *maps)
{
	if (maps->E_texture)
	{
		free(maps->E_texture);
		maps->E_texture = NULL;
	}
	if (maps->N_texture)
	{
		free(maps->N_texture);
		maps->N_texture = NULL;
	}
	if (maps->S_texture)
	{
		free(maps->S_texture);
		maps->S_texture = NULL;
	}
	if (maps->W_texture)
	{
		free(maps->W_texture);
		maps->W_texture = NULL;
	}
	if (maps->map)
		free_d_arr(maps->map);
}
