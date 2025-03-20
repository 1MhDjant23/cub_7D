/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:54:38 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/19 14:07:53 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_view(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	field_of_view(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int	player_position(t_game *game, int x, int y, int i)
{
	int	j;

	j = 0;
	while (game->data->maps->map[i][j] != '\0')
	{
		if (game->data->maps->map[i][j] == 'N'
		|| game->data->maps->map[i][j] == 'S'
		|| game->data->maps->map[i][j] == 'E'
		|| game->data->maps->map[i][j] == 'W')
		{
			game->player_x = x + (TILESIZE / 2);
			game->player_y = y + (TILESIZE / 2);
			check_dir(game);
			return (0);
		}
		x += TILESIZE;
		j++;
	}
	return (1);
}

void	init_game_data(t_game *game)
{
	int	x;
	int	y; 
	int	i;

	x = 0;
	y = 0;
	i = 0;
	game->ray = malloc(sizeof(ray_cast) * WIDTH);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	save_pixels(game);//mait
	while (game->data->maps->map[i])
	{
		if (player_position(game, x, y, i) == 0)
			break ;
		y += TILESIZE;
		x = 0;
		i++;
	}
	field_of_view(game);
}
