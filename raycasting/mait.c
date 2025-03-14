/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:37 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/13 22:29:09 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*load_textures(char *texturePNG)
{
	mlx_texture_t	*tmpTexture;
	tmpTexture = mlx_load_png(texturePNG);
	if (!tmpTexture)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	return (tmpTexture);
}

void	load_images(t_game *game)
{

	game->pixels->EA = mlx_texture_to_image(game->mlx, load_textures(game->data->maps->E_texture));
	if (!game->pixels->EA)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	game->pixels->NO = mlx_texture_to_image(game->mlx, load_textures(game->data->maps->N_texture));
	if (!game->pixels->NO)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	game->pixels->WE = mlx_texture_to_image(game->mlx, load_textures(game->data->maps->W_texture));
	if (!game->pixels->WE)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	game->pixels->SO = mlx_texture_to_image(game->mlx, load_textures(game->data->maps->S_texture));
	if (!game->pixels->WE)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
}

int	**get_pexels(mlx_image_t *img)
{
	int	**pex;
	size_t	i;
	size_t	j;
	size_t	count;


	count = 0;
	i = 0;
	if (!img)
		return (NULL);
	pex = (int**)malloc(sizeof(int*) * img->height);
	if (!pex)
		exit(write(2, "Error, malloc\n", 14));
	while (i < img->height)
	{
		j = 0;
		pex[i] = malloc(sizeof(int) * img->width);
		if (!pex[i])
			exit(write(2, "malloc\n", 7));
		while (j < img->width)
		{
			pex[i][j++] = get_rgba(img->pixels[count], img->pixels[count + 1], img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
		i++;
	}
	return (pex);
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8| a);
}


void	save_pixels(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
    load_images(game);//mait
	
	game->pixels->NO_Pexel = get_pexels(game->pixels->NO);
	game->pixels->WE_Pexel = get_pexels(game->pixels->WE);
	game->pixels->EA_Pexel = get_pexels(game->pixels->EA);
	game->pixels->SO_Pexel = get_pexels(game->pixels->SO);

}

int	get_offset_X(mlx_image_t *img, t_game *game, int count_ray)
{
	int	offset;

	if (game->ray[count_ray].H_or_V)
		offset = ((game->ray[count_ray].x_ray / TILESIZE) - floor(game->ray[count_ray].x_ray / TILESIZE)) * img->width;
	else
		offset = ((game->ray[count_ray].y_ray / TILESIZE) - floor(game->ray[count_ray].y_ray / TILESIZE)) * img->width;
	return (offset);
}

int	get_offset_Y(mlx_image_t *img, t_game *game, int j, double line_H)
{
	int	offset;
	(void)game;
	(void)img;
	offset = (j / line_H) * img->height;
	return (offset);
}

void	draw_wall(int *start_wall, t_game *game, int ray_counter, double line_H,  double value )
{
	//first select image
	int	j;
	// mlx_image_t	*img = game->pixels->SO;
	int	offset_x;
	int	offset_y;
	// int	top_P = (HEIGHT / 2) - (line_H / 2);
	j = *start_wall ;
	offset_y = 0;
	offset_x = get_offset_X(game->pixels->SO, game, ray_counter);
	while ( *start_wall < value)
	{
		if (*start_wall >= HEIGHT)
			break;
		offset_y = get_offset_Y(game->pixels->SO, game, *start_wall - j, line_H);
			// printf("offset_x = %d, offset_y = %d\n", offset_x, offset_y);
		// if (*start_wall >= HEIGHT)
		// 	break;
		if ( *start_wall >= 0)
			mlx_put_pixel(game->img, ray_counter, *start_wall, game->pixels->SO_Pexel[offset_y][offset_x]);
		// }
		// else
		// {
		// 	break;	
		// }
		// start_end[0]++;
		(*start_wall)++;
		// j++;
		//inside each ray
	}
	
	

}

int	get_color_from_distance(double distance)
{
	unsigned char	r,g,b;

	if (distance < 1)
		distance = 1;
	r = 105 / distance;
	g = 255 / distance;
	b = 255 / distance;
	
	return (r << 16 | g << 8 | b);
}
