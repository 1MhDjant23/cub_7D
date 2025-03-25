/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:37 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 15:25:40 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_images(t_game *game, mlx_image_t **img, char *text)
{
	mlx_texture_t	*tmp_texture;

	tmp_texture = mlx_load_png(text);
	if (!tmp_texture)
	{
		mlx_delete_image(game->mlx, game->img);
		free_map_ele(game->data->maps);
		exit(STDERR_FILENO);
	}
	*img = mlx_texture_to_image(game->mlx, tmp_texture);
	if (!*img)
	{
		write(2, "Faillure to load PNG\n", 21);
		free_map_ele(game->data->maps);
		exit(STDERR_FILENO);
	}
	mlx_delete_texture(tmp_texture);
	tmp_texture = NULL;
}

int	**get_pexels(mlx_image_t *img)
{
	int		**pex;
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = -1;
	if (!img)
		return (NULL);
	pex = (int **)malloc(sizeof(int *) * img->height);
	while (++i < img->height)
	{
		j = 0;
		pex[i] = malloc(sizeof(int) * img->width);
		if (!pex || !pex[i])
			exit(write(2, "malloc\n", 7));
		while (j < img->width)
		{
			pex[i][j++] = get_rgba(img->pixels[count], img->pixels[count + 1], \
				img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
	}
	return (pex);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	save_pixels(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	load_images(game, &game->pixels->so, game->data->maps->s_texture);
	load_images(game, &game->pixels->no, game->data->maps->n_texture);
	load_images(game, &game->pixels->we, game->data->maps->w_texture);
	load_images(game, &game->pixels->ea, game->data->maps->e_texture);
	game->pixels->no_pexel = get_pexels(game->pixels->no);
	game->pixels->we_pexel = get_pexels(game->pixels->we);
	game->pixels->ea_pexel = get_pexels(game->pixels->ea);
	game->pixels->so_pexel = get_pexels(game->pixels->so);
}
