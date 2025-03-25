/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_intersections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:31:00 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/25 15:27:09 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	find_horz_intr(t_game *game, int j, double *x_raydir, double *y_raydir)
{
	double	y_steps;

	y_steps = TILESIZE;
	if (game->ray[j].facing_y == UP)
	{
		(*y_raydir) = floor(game->player_y / TILESIZE) * TILESIZE - 0.0001;
		y_steps = -TILESIZE;
	}
	else
		(*y_raydir) = (floor(game->player_y / TILESIZE) * TILESIZE) + TILESIZE;
	(*x_raydir) = (((*y_raydir) - game->player_y) / tan(game->ray->r_angle)) \
	+ game->player_x;
	return (y_steps);
}

void	find_horizontal(t_game *game, int j)
{
	double	y_steps;
	double	x_steps;
	double	x_raydir;
	double	y_raydir;

	facing(game, j);
	y_steps = find_horz_intr(game, j, &x_raydir, &y_raydir);
	x_steps = y_steps / tan(game->ray->r_angle);
	while (x_raydir >= 0 && y_raydir >= 0)
	{
		if ((y_raydir) / TILESIZE >= (game->data->maps->column)
			|| (x_raydir) / TILESIZE >= game->data->maps->rwo || \
		(y_raydir) / TILESIZE < 0 || (x_raydir) / TILESIZE < 0)
			break ;
		if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)] \
			[(int)floor(x_raydir / TILESIZE)] == '1')
			break ;
		y_raydir += y_steps;
		x_raydir += x_steps;
	}
	game->ray->hx = x_raydir;
	game->ray->hy = y_raydir;
}

double	find_vert_intr(t_game *game, int j, double *x_raydir, double *y_raydir)
{
	double	x_steps;

	x_steps = TILESIZE;
	if (game->ray[j].facing_x == RIGHT)
		(*x_raydir) = (floor(game->player_x / TILESIZE) * TILESIZE) + TILESIZE ;
	else
	{
		(*x_raydir) = ((floor(game->player_x / TILESIZE)) * TILESIZE) - 0.0001;
		x_steps = -TILESIZE; 
	}
	(*y_raydir) = game->player_y + ((*x_raydir) - game->player_x) \
		* tan(game->ray->r_angle);
	return (x_steps);
}

void	find_vertical(t_game *game, int j)
{
	double	y_steps;
	double	x_steps;
	double	x_raydir;
	double	y_raydir;

	facing(game, j);
	x_steps = find_vert_intr(game, j, &x_raydir, &y_raydir);
	y_steps = x_steps * tan(game->ray->r_angle); 
	while (x_raydir >= 0 && y_raydir >= 0)
	{
		if ((y_raydir) / TILESIZE >= (game->data->maps->column)
			|| (x_raydir) / TILESIZE >= game->data->maps->rwo || \
		(y_raydir) / TILESIZE < 0 || (x_raydir) / TILESIZE < 0)
			break ;
		if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)] \
			[(int)floor(x_raydir / TILESIZE)] == '1')
			break ;
		x_raydir += x_steps;
		y_raydir += y_steps;
	}
	game->ray->vx = x_raydir;
	game->ray->vy = y_raydir;
}
