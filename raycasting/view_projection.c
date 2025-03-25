/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:39:31 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/25 15:27:39 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_3d(t_game *game)
{
	int		i;
	int		j;
	double	line_height;
	double	distance_windows;
	double	value;

	i = 0;
	distance_windows = (WIDTH / 2) / tan(deg_to_rad(FOV) / 2);
	while (i < WIDTH)
	{
		line_height = (TILESIZE / game->ray[i].distance) * HEIGHT;
		j = 0;
		value = (HEIGHT - line_height) / 2;
		while (j < value && j < HEIGHT)
			mlx_put_pixel(game->img, i, j++, game->data->maps->ce_color);
		j = value;
		draw_wall(&j, game, i, line_height);
		while (j < HEIGHT)
			mlx_put_pixel(game->img, i, j++, game->data->maps->fl_color);
		i++;
	}
}

void	set_ray_distance(t_game *game, int j)
{
	double	distance_h;
	double	distance_v;

	distance_h = sqrt(pow(game->ray->hx - game->player_x, 2) \
	+ pow(game->ray->hy - game->player_y, 2));
	distance_v = sqrt(pow(game->ray->vx - game->player_x, 2) \
	+ pow(game->ray->vy - game->player_y, 2));
	if (distance_h < distance_v)
	{
		game->ray[j].distance = distance_h;
		game->ray[j].x_ray = game->ray->hx;
		game->ray[j].y_ray = game->ray->hy;
		game->ray[j].h_or_v = true;
	}
	else
	{
		game->ray[j].distance = distance_v;
		game->ray[j].x_ray = game->ray->vx;
		game->ray[j].y_ray = game->ray->vy;
		game->ray[j].h_or_v = false;
	}
}

void	field_of_view(t_game *game)
{
	int	j;

	j = 0;
	game->ray->r_angle = game->dir_angle - (deg_to_rad(FOV) / 2);
	while (j < WIDTH)
	{
		game->ray->r_angle = normalize_ray_angle(game->ray->r_angle);
		find_horizontal(game, j);
		find_vertical(game, j);
		set_ray_distance(game, j);
		game->ray[j].distance *= cos(game->ray->r_angle - game->dir_angle);
		game->ray->r_angle += deg_to_rad(FOV) / WIDTH;
		j++;
	}
	draw_3d(game);
}
