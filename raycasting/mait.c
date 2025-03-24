/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:37 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/23 14:23:56 by mait-taj         ###   ########.fr       */
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
	game->pixels->EA = mlx_texture_to_image(game->mlx, \
		load_textures(game->data->maps->E_texture));
	if (!game->pixels->EA)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	// printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	game->pixels->NO = mlx_texture_to_image(game->mlx, \
		load_textures(game->data->maps->N_texture));
	if (!game->pixels->NO)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	game->pixels->WE = mlx_texture_to_image(game->mlx, \
		load_textures(game->data->maps->W_texture));
	if (!game->pixels->WE)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
	game->pixels->SO = mlx_texture_to_image(game->mlx, \
		load_textures(game->data->maps->S_texture));
	if (!game->pixels->SO)
	{
		write(2, "Faillure to load PNG\n", 21);
		exit(EXIT_FAILURE);
	}
}

int	**get_pexels(mlx_image_t *img)
{
	int		**pex;
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
			pex[i][j++] = get_rgba(img->pixels[count], img->pixels[count + 1],\
				img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
		i++;
	}
	return (pex);
}

int	get_rgba(int r, int g, int b, int a)
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

int	get_offset_Y(mlx_image_t *img, int j, double line_H)
{
	int	offset;

	offset = (j / line_H) * img->height;
	return (offset);
}

int adjust_color_by_distance(int color, double distance)
{
    unsigned char r, g, b;

    if (distance < 1)
        distance = 1;

    // Extract RGB components from the int color
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    // Adjust each component by the distance
    r = r / distance;
    g = g / distance;
    b = b / distance;

    // Combine the adjusted components back into an int
    return (r << 16 | g << 8 | b);
}
mlx_image_t	*select_texture_to_put(t_game *game, int r_counter, int ***color)
{
	if (!game->ray[r_counter].H_or_V && game->ray[r_counter].facing_x == LEFT)
	{
		*color = game->pixels->SO_Pexel;
		return (game->pixels->SO);
	}
	else if (!game->ray[r_counter].H_or_V && game->ray[r_counter].facing_x == RIGHT)
	{
		*color = game->pixels->NO_Pexel;
		return (game->pixels->NO);
	}
	else if (game->ray[r_counter].H_or_V && game->ray[r_counter].facing_y == DOWN)
	{
		*color = game->pixels->WE_Pexel;
		return (game->pixels->WE);
	}
	else if (game->ray[r_counter].H_or_V && game->ray[r_counter].facing_y == UP)
	{
		*color = game->pixels->EA_Pexel;
		return (game->pixels->EA);
	}
	return (NULL);
}

void	draw_wall(int *start_wall, t_game *game, int ray_counter, double line_H)
{
	int	top_Wall;
	int	bottom_Wall;
	int	offset_x;
	int	offset_y;
	int	**color;
	mlx_image_t	*img;

	img = select_texture_to_put(game, ray_counter, &color);
	top_Wall = *start_wall;
	bottom_Wall = top_Wall + line_H;
	offset_x = get_offset_X(img, game, ray_counter);
	offset_y = 0;
	while (*start_wall < bottom_Wall)
	{
		if (*start_wall >= HEIGHT)
			break;
		offset_y = get_offset_Y(img, *start_wall - top_Wall, line_H);
		if ( *start_wall >= 0)
			mlx_put_pixel(game->img, ray_counter, *start_wall, color[offset_y][offset_x]);
		(*start_wall)++;
	}
}

// int	get_color_from_distance(double distance)
// {
// 	unsigned char	r,g,b;

// 	if (distance < 1)
// 		distance = 1;
// 	r = 105 / distance;
// 	g = 255 / distance;
// 	b = 255 / distance;
	
// 	return (r << 16 | g << 8 | b);
// }
