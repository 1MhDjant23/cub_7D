/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:51:00 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 15:34:11 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	free_struct(t_cub *data)
{
	t_fil	*temp;

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
	if (maps->e_texture)
	{
		free(maps->e_texture);
		maps->e_texture = NULL;
	}
	if (maps->n_texture)
	{
		free(maps->n_texture);
		maps->n_texture = NULL;
	}
	if (maps->s_texture)
	{
		free(maps->s_texture);
		maps->s_texture = NULL;
	}
	if (maps->w_texture)
	{
		free(maps->w_texture);
		maps->w_texture = NULL;
	}
	if (maps->map)
		free_d_arr(maps->map);
}

int	destroy_texture(t_game *game)
{
	free(game->ray);
	free_dint(game->pixels->no_pexel, game->pixels->no);
	free_dint(game->pixels->so_pexel, game->pixels->so);
	free_dint(game->pixels->we_pexel, game->pixels->we);
	free_dint(game->pixels->ea_pexel, game->pixels->ea);
	if (game->pixels->no)
		mlx_delete_image(game->mlx, game->pixels->no);
	if (game->pixels->so)
		mlx_delete_image(game->mlx, game->pixels->so);
	if (game->pixels->we)
		mlx_delete_image(game->mlx, game->pixels->we);
	if (game->pixels->ea)
		mlx_delete_image(game->mlx, game->pixels->ea);
	free_map_ele(game->data->maps);
	return (1);
}
