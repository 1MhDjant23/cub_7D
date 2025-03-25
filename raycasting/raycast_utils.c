/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:37:13 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/22 19:52:47 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double angle)
{
	return (angle * (M_PI / 180));
}

double	normalize_ray_angle(double angle)
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	check_dir(t_game *game)
{
	int	i;
	int	j;

	i = (int)(game->player_y / TILESIZE);
	j = (int)(game->player_x / TILESIZE);
	if (game->data->maps->map[i][j] == 'N')
		game->dir_angle = 3 * M_PI_2;
	else if (game->data->maps->map[i][j] == 'S')
		game->dir_angle = M_PI_2;
	else if (game->data->maps->map[i][j] == 'E')
		game->dir_angle = 0;
	else if (game->data->maps->map[i][j] == 'W')
		game->dir_angle = M_PI;
}

void	facing(t_game *game, int j)
{
	if (game->ray->r_angle >= 0 && game->ray->r_angle < M_PI)
		game->ray[j].facing_y = DOWN;
	else
		game->ray[j].facing_y = UP;
	if (game->ray->r_angle >= M_PI_2 && game->ray->r_angle < 3 * M_PI_2)
		game->ray[j].facing_x = LEFT;
	else
		game->ray[j].facing_x = RIGHT;
}

void	update_position(t_game *game, int find, double nx, double ny)
{
	if ((game->data->maps->map[(int)ny / TILESIZE] \
		[(int)nx / TILESIZE] != '1') && find != -1) 
	{
		game->player_x = nx;
		game->player_y = ny;
	}
	return ;
}
