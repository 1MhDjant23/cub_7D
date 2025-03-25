/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:09:56 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 14:26:15 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_offset_x(mlx_image_t *img, t_game *game, int count_ray)
{
	int	offset;

	if (game->ray[count_ray].H_or_V)
		offset = ((game->ray[count_ray].x_ray / TILESIZE) - floor(game
					->ray[count_ray].x_ray / TILESIZE)) * img->width;
	else
		offset = ((game->ray[count_ray].y_ray / TILESIZE) - floor(game
					->ray[count_ray].y_ray / TILESIZE)) * img->width;
	return (offset);
}

int	get_offset_y(mlx_image_t *img, int j, double line_H)
{
	int	offset;

	offset = (j / line_H) * img->height;
	return (offset);
}

mlx_image_t	*select_texture_to_put(t_game *game, int r_counter, int ***color)
{
	if (!game->ray[r_counter].H_or_V && game->ray[r_counter].facing_x == LEFT)
	{
		*color = game->pixels->WE_Pexel;
		return (game->pixels->WE);
	}
	else if (!game->ray[r_counter].H_or_V && game
		->ray[r_counter].facing_x == RIGHT)
	{
		*color = game->pixels->EA_Pexel;
		return (game->pixels->EA);
	}
	else if (game->ray[r_counter].H_or_V && game
		->ray[r_counter].facing_y == DOWN)
	{
		*color = game->pixels->SO_Pexel;
		return (game->pixels->SO);
	}
	else if (game->ray[r_counter].H_or_V && game->ray[r_counter].facing_y == UP)
	{
		*color = game->pixels->NO_Pexel;
		return (game->pixels->NO);
	}
	return (NULL);
}

void	draw_wall(int *start_wall, t_game *game, int ray_counter, double line_H)
{
	int			top_wall;
	int			bottom_wall;
	int			offset_x;
	int			offset_y;
	int			**color;

	top_wall = *start_wall;
	bottom_wall = top_wall + line_H;
	offset_x = get_offset_x(select_texture_to_put(game, ray_counter, &color),
			game, ray_counter);
	offset_y = 0;
	while (*start_wall < bottom_wall)
	{
		if (*start_wall >= HEIGHT)
			break ;
		offset_y = get_offset_y(select_texture_to_put(game, ray_counter,
					&color), *start_wall - top_wall, line_H);
		if (*start_wall >= 0)
			mlx_put_pixel(game->img, ray_counter, *start_wall,
				color[offset_y][offset_x]);
		(*start_wall)++;
	}
}
