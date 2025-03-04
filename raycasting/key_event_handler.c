/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:17 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/03 21:11:04 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_move(mlx_key_data_t keydata, t_game *game, double *nx, double *ny)
{
	if (keydata.key == MLX_KEY_A && keydata.action)
    {
        (*nx) += SPEED * cos(game->dir_angle - M_PI_2);
        (*ny) += SPEED * sin(game->dir_angle - M_PI_2);
    }
    else if (keydata.key == MLX_KEY_D && keydata.action)
    {
        (*nx) -= SPEED * cos(game->dir_angle - M_PI_2);
        (*ny) -= SPEED * sin(game->dir_angle - M_PI_2);
    }
    else if (keydata.key == MLX_KEY_W && keydata.action)
    {
        (*nx) += SPEED * cos(game->dir_angle);
        (*ny) += SPEED * sin(game->dir_angle);
    }
    else if (keydata.key == MLX_KEY_S && keydata.action)
    {
    	(*nx) -= SPEED * cos(game->dir_angle);
        (*ny) -= SPEED * sin(game->dir_angle);
    }
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
		if (game->data->maps->map[(int)(ny_check)/ TILESIZE][(int)(nx_check) / TILESIZE] == '1')
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
	int i;

	i = 0;
	while (i < 4)
    {
		if (check_wall(game, nx, ny, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game;
    game = (t_game *)param;
    double nx, ny;
    int find = 0;
	
    nx = game->player_x;
    ny = game->player_y;
    if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_W)
    {
		player_move(keydata, game, &nx, &ny);
        if (check_for_walls(game, nx, ny) == -1)
            find = -1;
        if ((game->data->maps->map[(int)ny / TILESIZE][(int)nx / TILESIZE] != '1') && find != -1) 
        {
            game->player_x = nx;
            game->player_y = ny;                   
            mlx_delete_image(game->mlx, game->img);
            render_view(game);
        }
    }
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action)
    {
        game->dir_angle += 0.1;
        game->dir_angle = normalize_ray_angle(game->dir_angle);
        mlx_delete_image(game->mlx, game->img);
        render_view(game);
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action)
    {
        game->dir_angle -=0.1;
        game->dir_angle = normalize_ray_angle(game->dir_angle);
        mlx_delete_image(game->mlx, game->img);
        render_view(game);
    }
     if (keydata.key == MLX_KEY_ESCAPE)
    {
        exit(0);
    }
}
