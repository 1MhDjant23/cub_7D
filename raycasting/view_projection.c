/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_gamerojection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:31:00 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/03 22:40:32 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void find_horizontal(t_game *game, int j)
{
    double y_steps;
    double x_steps;
    double x_raydir;
    double y_raydir;
     
    y_steps = TILESIZE;
    x_raydir = 0;
    y_raydir = 0;
    facing(game, j);
    if (game->ray[j].facing_y == UP)
    {
        y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE - 0.0001);    
        y_steps = - TILESIZE; 
    }
    else if(game->ray[j].facing_y == DOWN) 
        y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE) + TILESIZE; 
   x_raydir = ((y_raydir - game->player_y) / tan(game->ray->r_angle)) + game->player_x;
    x_steps = y_steps / tan(game->ray->r_angle);
    while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
    {
           if ((y_raydir)/TILESIZE >= (game->data->maps->column  - 1 ) || (x_raydir)/TILESIZE >= game->data->maps->rwo ||
            (y_raydir)/TILESIZE < 0 || (x_raydir)/TILESIZE < 0)
                break;
        if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
            break ; 
        if (check(game, y_raydir, x_raydir) == -1)
            break ;  
        y_raydir += y_steps;
        x_raydir += x_steps;
    }
    game->ray->Hx = x_raydir;
    game->ray->Hy = y_raydir;
}

void find_vertical(t_game *game, int j)
{
    double y_steps;
    double x_steps;
    double x_raydir;
    double y_raydir;

    x_steps = TILESIZE;
    x_raydir = 0;
    y_raydir = 0;
    facing(game, j);
    if (game->ray[j].facing_x  == RIGHT)
        x_raydir = (floor(game->player_x / TILESIZE) * TILESIZE) + TILESIZE ;
    else if(game->ray[j].facing_x  == LEFT)
    {
        x_raydir = ((floor(game->player_x / TILESIZE)) * TILESIZE) - 0.0001;
        x_steps = - TILESIZE; 
    }
    y_raydir = game->player_y + (x_raydir - game->player_x) * tan(game->ray->r_angle);
    y_steps = x_steps * tan(game->ray->r_angle); 
    while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
    {
      if ((y_raydir)/TILESIZE >= (game->data->maps->column  - 1 ) || (x_raydir)/TILESIZE >= game->data->maps->rwo ||
            (y_raydir)/TILESIZE < 0 || (x_raydir)/TILESIZE < 0)
                break;
        if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
            break ;
        if (check(game, y_raydir, x_raydir) == -1)
            break ;   
        x_raydir += x_steps;
        y_raydir += y_steps;
    }
    game->ray->Vx = x_raydir;
    game->ray->Vy = y_raydir;
 
}

void draw_3d(t_game *game)
{
    
    int i = 0;
    int j = 0;
    double line_height;
    double distance_windows = (WIDTH / 2) / tan(deg_to_rad(FOV)/2);
    double value;

    while (i < WIDTH)
    {
        line_height = (TILESIZE / game->ray[i].distance) * distance_windows;
        j = 0;
        value = (HEIGHT - line_height) / 2;
        while (j < value && j < HEIGHT)
           mlx_put_pixel(game->img, i, j++, game->data->maps->CE_color);
        j = value;//when line height greather than HEIGHT
        draw_wall(&j, game, i, line_height);
        while (j < HEIGHT)
           mlx_put_pixel(game->img, i, j++, game->data->maps->FL_color);
        i++;
    }
}


void	set_ray_distance(t_game *game, int j)
{
	double	distance_h;
	double	distance_v;

	distance_h = sqrt(pow(game->ray->Hx - game->player_x, 2) + pow(game->ray->Hy - game->player_y, 2));
	distance_v = sqrt(pow(game->ray->Vx - game->player_x, 2) + pow(game->ray->Vy - game->player_y, 2));
	if (distance_h < distance_v)
	{
		game->ray[j].distance = distance_h;
		game->ray[j].x_ray = game->ray->Hx;
		game->ray[j].y_ray = game->ray->Hy;
        game->ray[j].H_or_V = true;// true because horizontal
	}
	else
	{
		game->ray[j].distance = distance_v;
		game->ray[j].x_ray = game->ray->Vx;
		game->ray[j].y_ray = game->ray->Vy;
        game->ray[j].H_or_V = false;// false because verticale

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
