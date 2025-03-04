/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:19:16 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/02 17:19:58 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void dda(t_game *game , int color, double  x1, double y1)
{
    int steps;
    double dx, dy ,yinc, xinc;

    dx = (x1 - game->player_x);
    dy = (y1 - game->player_y);
    steps = fabs(dy);
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    xinc = dx/steps;
    yinc = dy/steps;
    dx = game->player_x;
    dy = game->player_y;
    for(int i = 0; i <= steps; i++)
    {   
        if(dx < 0 || dy < 0 || dx >= WIDTH || dy >= HEIGHT)
            break;
        mlx_put_pixel(game->img, round(dx), round(dy), color);
        dx += xinc;
        dy += yinc; 
    }
}
