/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:51:00 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/13 16:35:12 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	free_all_data(t_cub *data)
{
	// if (data->file)
	// {
	// 	free(data->file);
	// 	data->file = NULL;
	// }
	if (data->line_m)
	{
		free(data->line_m);
		data->line_m = NULL;
	}
	free_d_arr(data->map);
}

void	free_map_ele(t_map *maps)
{
	// if (maps->CE_color)
	// {
	// 	free(maps->CE_color);
	// 	maps->CE_color = NULL;
	// }
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
	// if (maps->FL_color)
	// {
	// 	free(maps->FL_color);
	// 	maps->FL_color = NULL;
	// }		
}
