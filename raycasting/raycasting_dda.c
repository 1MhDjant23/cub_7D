/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:19:16 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/19 19:24:21 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_segment(t_game *game, double x1, double y1, int steps)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	dx = game->player_x;
	dy = game->player_y;
	while (i <= steps)
	{
		if (dx < 0 || dy < 0 || dx >= WIDTH || dy >= HEIGHT)
			break ;
		dx += (x1 - game->player_x / steps);
		dy += (y1 - game->player_y / steps); 
	}
}

void	dda(t_game *game, double x1, double y1)
{
	int		steps;
	double	xinc;
	double	yinc;

	steps = fabs(y1 - game->player_y);
	if (fabs(x1 - game->player_x) > fabs(y1 - game->player_y))
		steps = fabs(x1 - game->player_x);
	xinc = (x1 - game->player_x / steps);
	yinc = (y1 - game->player_y / steps);
	draw_line_segment(game, x1, y1, steps);
}

// void	dda(t_game *game, int color, double x1, double y1)
// {
// 	double	dx;
// 	double	dy;
// 	double	yinc;
// 	double	xinc;

// 	xinc = dx / calculat_steps(game, x1, y1);
// 	yinc = dy / calculat_steps(game, x1, y1);
// 	dx = game->player_x;
// 	dy = game->player_y;
// 	for (int i = 0; i <= calculat_steps(game, x1, y1); i++)
// 	{
// 		if (dx < 0 || dy < 0 || dx >= WIDTH || dy >= HEIGHT)
// 			break ;
// 		mlx_put_pixel(game->img, round(dx), round(dy), color);
// 		dx += xinc;
// 		dy += yinc; 
// 	}
// }
