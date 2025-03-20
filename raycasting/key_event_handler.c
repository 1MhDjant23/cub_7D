/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:17 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/19 19:20:42 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	player_move(t_game *game, double *nx, double *ny)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		(*nx) += SPEED * cos(game->dir_angle - M_PI_2);
		(*ny) += SPEED * sin(game->dir_angle - M_PI_2);
		return (true);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		(*nx) -= SPEED * cos(game->dir_angle - M_PI_2);
		(*ny) -= SPEED * sin(game->dir_angle - M_PI_2);
		return (true);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		(*nx) += SPEED * cos(game->dir_angle);
		(*ny) += SPEED * sin(game->dir_angle);
		return (true);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		(*nx) -= SPEED * cos(game->dir_angle);
		(*ny) -= SPEED * sin(game->dir_angle);
		return (true);
	}
	return (false);
}

int	check_wall(t_game *game, double nx, double ny, int i)
{
	double	nx_check;
	double	ny_check;
	int		j;
	int		find;

	nx_check = nx;
	ny_check = ny;
	j = 0; 
	find = 0;
	while (j < 4)
	{
		if (game->data->maps->map[(int)(ny_check) / TILESIZE] \
			[(int)(nx_check) / TILESIZE] == '1')
			find = -1;
		if (i == 0)
			nx_check++;
		else if (i == 1)
			nx_check--;
		else if (i == 2)
			ny_check++;
		else if (i == 3)
			ny_check--;
		j++;
	}
	return (find);
}

int	check_for_walls(t_game *game, double nx, double ny)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (check_wall(game, nx, ny, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

bool	angle_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->dir_angle += 0.1;
		game->dir_angle = normalize_ray_angle(game->dir_angle);
		return (true);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->dir_angle -= 0.1;
		game->dir_angle = normalize_ray_angle(game->dir_angle);
		return (true);
	}
	return (false);
}

void	key_hook( void *param)
{
	t_game	*game;
	game = (t_game *)param;
	double nx, ny;
	int find = 0;
	bool	a;
	bool	b;

	nx = game->player_x;
	ny = game->player_y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
	a = player_move(game, &nx, &ny);
	if (check_for_walls(game, nx, ny) == -1)
		find = -1;
	b = angle_rotation(game);
	if ((game->data->maps->map[(int)ny / TILESIZE] \
		[(int)nx / TILESIZE] != '1') && find != -1) 
	{
		game->player_x = nx;
		game->player_y = ny;
	}
	if (a == true || b == true)
	{
		mlx_delete_image(game->mlx, game->img);
		render_view(game);
	}
}
