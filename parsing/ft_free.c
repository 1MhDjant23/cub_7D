/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:51:00 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/24 17:39:27 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	free_struct(t_cub *data)
{
	t_filling	*temp;

	while (data->filling)
	{
		temp = data->filling->next;
		if (data->filling->line)
		{
			free(data->filling->line);
			data->filling->line = NULL;
		}
		data->filling->line = NULL;
		if (data->filling)
		{
			free(data->filling);
			data->filling = NULL;
		}
		data->filling = temp;
	}
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

int	destroy_texture(t_game *game)
{
	free_dint(game->pixels->NO_Pexel, game->pixels->NO);
	free_dint(game->pixels->SO_Pexel, game->pixels->SO);
	free_dint(game->pixels->WE_Pexel, game->pixels->WE);
	free_dint(game->pixels->EA_Pexel, game->pixels->EA);
	if (game->pixels->NO)
		mlx_delete_image(game->mlx, game->pixels->NO);
	if (game->pixels->SO)
		mlx_delete_image(game->mlx, game->pixels->SO);
	if (game->pixels->WE)
		mlx_delete_image(game->mlx, game->pixels->WE);
	if (game->pixels->EA)
		mlx_delete_image(game->mlx, game->pixels->EA);
	free_map_ele(game->data->maps);
	return (1);
}
