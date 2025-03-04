/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:50:03 by felhafid          #+#    #+#             */
/*   Updated: 2025/03/04 11:38:41 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void square(mlx_image_t * img , double x, double y, int color)
// {
//     int nx = 0;
//     int ny = 0;
//     while (ny < TILESIZE)
//     {
//         nx = 0;
//         while (nx < TILESIZE)
//         {
//             if  ((ny == 0 || nx == 0 || nx == TILESIZE - 1 || ny == TILESIZE - 1) && color ==  0xffffffff)
//                 mlx_put_pixel(img, x + nx, y + ny, 0x7f7f7fff);
//             mlx_put_pixel(img, x + nx, y + ny, color);
//             nx++;
//         }
//         ny++;
//     }
//     return ;
// }

// void sphere(t_game *game, int color)
// {
//     (void)color;
//     int R = 3;
//     for (int y = game->player_y - R; y <= game->player_y + R; y++)
//     {
//         for (int x = game->player_x - R; x <= game->player_x + R; x++)
//         {
//             if ((x - game->player_x) * (x - game->player_x) + (y - game->player_y) * (y - game->player_y) <= R * R)
//             {
//                 mlx_put_pixel(game->img, x, y, color);
//             }
//         }
//     }
//     // field_of_view(game);
// }


// void square(mlx_image_t * img , double x, double y, int color)
// {
//     int nx = 0;
//     int ny = 0;
    
//     while (ny < TILESIZE)
//     {
//         nx = 0;
        
//             // printf("ny %d\n", ny);
//         while (nx < TILESIZE)
//         {
//             if  ((ny == 0 || nx == 0 || nx == TILESIZE - 1 || ny == TILESIZE - 1) && (unsigned int )color ==  0xffffffff)
//                 mlx_put_pixel(img, x + nx, y + ny, 0x7f7f7fff);
//             else 
//                 mlx_put_pixel(img, x + nx, y + ny, color);
//             nx++;
//         }
//         ny++;
//     }
//     return ;
// }
void square(mlx_image_t * img , double x, double y)
{
    int nx = 0;
    int ny = 0;
    while (ny < TILESIZE)
    {
        nx = 0;
        while (nx < TILESIZE)
        {
            mlx_put_pixel(img, x + nx, y + ny, 255);
            nx++;
        }
        ny++;
    }
    return ;
}

void square1(mlx_image_t * img , double x, double y)
{
    double nx = 0;
    double ny = 0;
    while (ny < TILESIZE)
    {
        nx = 0;
        while (nx < TILESIZE)
        {
            if (ny == 0 || nx == 0 || nx == TILESIZE - 1 || ny == TILESIZE - 1)
                mlx_put_pixel(img, x + nx, y + ny, 0x7f7f7fff);
            else
                mlx_put_pixel(img, x + nx, y + ny, 0xffffffff);
            nx++;
        }
        ny++;
    }
    return ;
}
double	deg_to_rad(double angle)
{
	return (angle * (M_PI / 180));
}

void check_dir(t_game *game)
{
    int i, j;
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

double	normalize_ray_angle(double angle)
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	else if(angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

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
void facing(t_game *game)
{
    if (game->ray->r_angle >= 0 && game->ray->r_angle < M_PI)
        game->ray->facing_y = DOWN;
    else
        game->ray->facing_y = UP;
    if (game->ray->r_angle >= M_PI_2 && game->ray->r_angle < 3 * M_PI_2)
        game->ray->facing_x = LEFT;
    else
        game->ray->facing_x = RIGHT;
}

int check(t_game *game, double y_ray, double x_ray)
{
    double x;
    double y;

    x = x_ray - 0.00001;
    y = y_ray;
    // printf("%f  ===> %f\n", y, x);
    // printf("everything is oky??\n");
    if (game->data->maps->map[(int)y/TILESIZE][(int)x / TILESIZE] == '1')
        return (-1);
    // printf("what\n");
    x = x_ray + 0.00001;
    if (game->data->maps->map[(int)y / TILESIZE][(int)x / TILESIZE] == '1')
        return (-1);
    y = y_ray + 0.00001;
    if (game->data->maps->map[(int)y/ TILESIZE][(int)x_ray / TILESIZE] == '1')
        return (-1);
    y = y_ray - 0.00001;
    if (game->data->maps->map[(int)y/ TILESIZE][(int)x_ray / TILESIZE] == '1')
        return (-1);
    return (0);
}

// void find_horizontal(t_game *game)
// {
//     double y_steps;
//     double x_steps;
//     double x_raydir;
//     double y_raydir;
     
//     y_steps = TILESIZE;
//     x_raydir = 0;
//     y_raydir = 0;
//     facing(game);
//     if (game->ray->facing_y == UP)
//     {
//         y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE -0.0001);    
//         y_steps = - TILESIZE; 
//     }
//     else if(game->ray->facing_y == DOWN) 
//         y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE) + TILESIZE; 
//    x_raydir = ((y_raydir - game->player_y) / tan(game->ray->r_angle)) + game->player_x;
//     x_steps = y_steps / tan(game->ray->r_angle);
//     while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
//     {
//            if ((y_raydir)/TILESIZE >= (game->data->maps->column - 1) || (x_raydir)/TILESIZE >= game->data->maps->rwo ||
//             (y_raydir)/TILESIZE < 0 || (x_raydir)/TILESIZE < 0 )
//                 break;
//         if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
//             break ; 
//         if (check(game, y_raydir, x_raydir) == -1)
//             break ;  
//         y_raydir += y_steps;
//         x_raydir += x_steps;
//     }
//     game->ray->Hx = x_raydir;
//     game->ray->Hy = y_raydir;
// }

// void find_vertical(t_game *game)
// {
//     double y_steps;
//     double x_steps;
//     double x_raydir;
//     double y_raydir;

//     x_steps = TILESIZE;
//     x_raydir = 0;
//     y_raydir = 0;
//     facing(game);
//     if (game->ray->facing_x  == RIGHT )
//         x_raydir = (floor(game->player_x / TILESIZE) * TILESIZE) + TILESIZE ;
//     else if(game->ray->facing_x  == LEFT)
//     {
//         x_raydir = ((floor(game->player_x / TILESIZE)) * TILESIZE) - 0.0001;
//         x_steps = - TILESIZE; 
//     }
//     y_raydir = game->player_y + (x_raydir - game->player_x) * tan(game->ray->r_angle);
//     y_steps = x_steps * tan(game->ray->r_angle); 
//     while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
//     {
//         if ((y_raydir)/TILESIZE >= (game->data->maps->column  - 1 ) || (x_raydir)/TILESIZE >= game->data->maps->rwo ||
//             (y_raydir)/TILESIZE < 0 || (x_raydir)/TILESIZE < 0)
//                 break;
//         if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
//             break ;
//         if (check(game, y_raydir, x_raydir) == -1)
//             break ;   
//         x_raydir += x_steps;
//         y_raydir += y_steps;
//     }
//     game->ray->Vx = x_raydir;
//     game->ray->Vy = y_raydir;
 
// }
void find_horizontal(t_game *game)
{
    //found vertical wall
    double y_steps;
    double x_steps;
    double x_raydir;
    double y_raydir;
     
    y_steps = TILESIZE;
        x_raydir = 0;
    y_raydir = 0;
    facing(game);
    if (game->ray->facing_y == UP)
    {
        // printf("UP\n");
        y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE -0.0001);    
        y_steps = - TILESIZE; 
    }
    else if(game->ray->facing_y == DOWN) 
    {
        // printf("DOWN \n");
        y_raydir = (floor(game->player_y / TILESIZE) * TILESIZE) + TILESIZE; 
    } 
   x_raydir = ((y_raydir - game->player_y) / tan(game->ray->r_angle)) + game->player_x;
    x_steps = y_steps / tan(game->ray->r_angle);
    while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
    {
           if ((int)(y_raydir)/TILESIZE >= (game->data->maps->column - 1) || (int)(x_raydir)/TILESIZE >= (game->data->maps->rwo) ||
            (int)(y_raydir)/TILESIZE < 0 || (int)(x_raydir)/TILESIZE < 0 ) {
                // printf("=================> ana hna\n");
                break;
            }
            
        // if ((int)floor(y_raydir / TILESIZE) == 7 && (int)floor(x_raydir / TILESIZE) == 13)
        //     printf("horizontal =====>  %d  =========> %d *****  %c \n", (int)floor(y_raydir / TILESIZE), (int)floor(x_raydir / TILESIZE), game->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)]);
        if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
        {
            // printf("====================> la hna \n");
            break ;
        }
        if (check(game, y_raydir, x_raydir) == -1)
        {
                // printf("what\n");
            break ;   
        }
            
        y_raydir += y_steps;
        x_raydir += x_steps;
    }
    game->ray->Hx = x_raydir;
    game->ray->Hy = y_raydir;
}

void find_vertical(t_game *game)
{
    double y_steps;
    double x_steps;
    double x_raydir;
    double y_raydir;

   //find the first point vertical
    x_steps = TILESIZE;
     x_raydir = 0;
    y_raydir = 0;
    facing(game);
    if (game->ray->facing_x  == RIGHT )
    {
        // printf("RIGHT \n");
        x_raydir = (floor(game->player_x / TILESIZE) * TILESIZE) + TILESIZE ;
    }
    else if(game->ray->facing_x  == LEFT)
    {
        // printf("LEFT \n");

        x_raydir = ((floor(game->player_x / TILESIZE)) * TILESIZE) - 0.0001;
        x_steps = - TILESIZE; 
    } 
    y_raydir = game->player_y + (x_raydir - game->player_x) * tan(game->ray->r_angle);
    y_steps = x_steps * tan(game->ray->r_angle); 
    while (x_raydir <= WIDTH && x_raydir >= 0 && y_raydir <= HEIGHT && y_raydir >= 0)
    {
        // printf("y ---> %d | x ---> %d\n", (int)(y_raydir)/TILESIZE, (int)(x_raydir)/TILESIZE);
         if ((int)(y_raydir)/TILESIZE >= (game->data->maps->column - 1) || (int)(x_raydir)/TILESIZE >= (game->data->maps->rwo) ||
            (int)(y_raydir)/TILESIZE < 0 || (int)(x_raydir)/TILESIZE < 0 ) {
                // printf("=================> ana hna\n");
                break;
            }
        // if ((int)floor(y_raydir / TILESIZE) == 7 && (int)floor(x_raydir / TILESIZE) == 13)
        //     printf("vertical =====>  %d  =========> %d *****  %c \n", (int)floor(y_raydir / TILESIZE), (int)floor(x_raydir / TILESIZE), game->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)]);
        if (game->data->maps->map[(int)floor(y_raydir / TILESIZE)][(int)floor(x_raydir / TILESIZE)] == '1')
        {
            // printf("====================> la hna \n");
            break ;
        }
         if (check(game, y_raydir, x_raydir) == -1)
        {
                // printf("what vert\n");
            break ;   
        }
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
        line_height = (TILESIZE/game->ray[i].distance) * distance_windows;
        j = 0;
        value = (HEIGHT - line_height) / 2;
        while (j < value && j < HEIGHT)
        {
            // printf("%d\n", j);
           mlx_put_pixel(game->img, i, j, 0x7f7f7fff);
           j++; 
        }
        while (j <= value + line_height && j < HEIGHT)
        {
            // printf("hna ana %d\n", j);
           mlx_put_pixel(game->img, i, j, 0xed2100ff);
           j++; 
        }
         while (j < HEIGHT)
        {
            // printf("talyta ana%d\n", j);
           mlx_put_pixel(game->img, i, j, 255);
           j++; 
        }
        // while (j <  HEIGHT)
        // {
        //     value = (HEIGHT - line_height) / 2;
        //     if (j <  value)
        //         mlx_put_pixel(p->img, i, j, 0x7f7f7fff);
        //     else if (j >= value && j <= value + line_height)
        //         mlx_put_pixel(p->img, i, j, 0xed2100ff);
        //     else if (j > value + line_height)
        //         mlx_put_pixel(p->img, i, j, 0x7f7f7fff);
        //     j++;
        // }
        i++;
    }
}

void field_of_view(t_game *game)
{
    double Dh;
    double Dv;
    int j = 0;
    game->ray->r_angle = game->dir_angle - (deg_to_rad(FOV) / 2);
    game->ray[j].x_ray = 0;
    game->ray[j].y_ray = 0;
    while (j < WIDTH)
    {
        game->ray->r_angle = normalize_ray_angle(game->ray->r_angle);
        find_horizontal(game);
        find_vertical(game);        
        Dh = sqrt(pow(game->ray->Hx - game->player_x, 2) + pow(game->ray->Hy - game->player_y, 2));
       Dv = sqrt(pow(game->ray->Vx - game->player_x, 2) + pow(game->ray->Vy - game->player_y, 2)); 
        if (Dh < Dv)
        { 
            game->ray[j].distance = Dh;
            game->ray[j].x_ray = game->ray->Hx;
            game->ray[j].y_ray = game->ray->Hy;
        }
        else
        {
            game->ray[j].distance = Dv;
            game->ray[j].x_ray = game->ray->Vx;
            game->ray[j].y_ray = game->ray->Vy;
        }
        // printf("%d\n", j);  
        game->ray[j].distance *= cos(game->ray->r_angle - game->dir_angle);
        
        // dda(game, 0xed2100ff,game->ray[j].x_ray, game->ray[j].y_ray);
        game->ray->r_angle += deg_to_rad(FOV) / WIDTH;
        j++;
    }
    draw_3d(game);
}

void sphere(t_game *game, int color)
{
    int R = 3;
    for (int y = game->player_y - R; y <= game->player_y + R; y++)
    {
        for (int x = game->player_x - R; x <= game->player_x + R; x++)
        {
            if ((x - game->player_x) * (x - game->player_x) + (y - game->player_y) * (y - game->player_y) <= R * R)
            {
                mlx_put_pixel(game->img, x, y, color);
            }
        }
    }
    field_of_view(game);
}

void init_(t_game *game)
{
     int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
     
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    while (game->data->maps->map[i])
    {
        j = 0;
        while (game->data->maps->map[i][j] != '\0')
        {
            if (game->data->maps->map[i][j] == '1')
                square(game->img, x, y);
            else if (game->data->maps->map[i][j] == '0' || game->data->maps->map[i][j] == 'W' ||
             game->data->maps->map[i][j] == 'N' || game->data->maps->map[i][j] == 'E' || game->data->maps->map[i][j] == 'S')
                square1(game->img, x, y);
            x += TILESIZE;
            j++;
        }
        y += TILESIZE;
        x = 0;
        i++;
    }
    sphere(game , 0xed2100ff);
    mlx_image_to_window(game->mlx, game->img, 0, 0);    
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game;
    game = (t_game *)param;
    double nx, ny;
    double nx1, ny1;
    int i = 0;
    int j;

    nx = game->player_x;
    ny = game->player_y;
    if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_W)
    {
        if (keydata.key == MLX_KEY_A && keydata.action)
        {
            nx += SPEED * cos(game->dir_angle - M_PI_2);
            ny += SPEED * sin(game->dir_angle - M_PI_2);
        }
        else if (keydata.key == MLX_KEY_D && keydata.action)
        {
            nx -= SPEED * cos(game->dir_angle - M_PI_2);
            ny -= SPEED * sin(game->dir_angle - M_PI_2);
        }
        else if (keydata.key == MLX_KEY_W && keydata.action)
        {
            nx += SPEED * cos(game->dir_angle);
            ny += SPEED * sin(game->dir_angle);
        }
        else if (keydata.key == MLX_KEY_S && keydata.action)
        {
            nx -= SPEED * cos(game->dir_angle);
            ny -= SPEED * sin(game->dir_angle);
        }
        nx1 = nx;
        ny1 = ny;
        int find = 0;
        while (i < 4)
        {
            nx1 = nx;
            ny1 = ny;
            j = 0; 
            while (j < 5)
            {
                if (game->data->maps->map[(int)(ny1)/ TILESIZE][(int)(nx1) / TILESIZE] == '1')
                    find = -1;
                if (i == 0)
                    nx1++;
                else if (i == 1)
                    nx1--;
                else if (i == 2)
                    ny1++;
                else if (i == 3)
                    ny1--;
                j++;
            }
            i++;
        }
        if ((game->data->maps->map[(int)ny / TILESIZE][(int)nx / TILESIZE] != '1') && find != -1) 
        {
            game->player_x = nx;
            game->player_y = ny;                   
            mlx_delete_image(game->mlx, game->img);
            init_(game);
        }
    }
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action)
    {
        game->dir_angle += 0.1;
        game->dir_angle = normalize_ray_angle(game->dir_angle);
        mlx_delete_image(game->mlx, game->img);
        init_(game);
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action)
    {
        game->dir_angle -=0.1;
        game->dir_angle = normalize_ray_angle(game->dir_angle);
        mlx_delete_image(game->mlx, game->img);
        init_(game);
    }
     if (keydata.key == MLX_KEY_ESCAPE)
    {
        exit(0);
    }
}

// void init_game_data(t_game *game)
// {
//     // ray_cast ray;
//     int x = 0;
//     int y = 0;    
//     int	i = 0;
//     int j = 0;
    
//     // calcul_row_col(game);
//     game->ray = malloc(sizeof(ray_cast) * WIDTH);
//     // game->ray = &ray;
//     game->img = mlx_new_image(game->mlx, WIDTH,HEIGHT);
//     while (game->data->maps->map[i])
//     {
//         j = 0; 
//         // printf("=================> %d\n", i);
//         while (game->data->maps->map[i][j] != '\0')
//         {
//             if (game->data->maps->map[i][j] == '1')
//             {
//                 square(game->img, x, y, 255);
//                 // printf("ana f '1'   %d\n", j);
                
//             }
//             else if (game->data->maps->map[i][j]  == '0' || game->data->maps->map[i][j]  == 'N' || game->data->maps->map[i][j]  == 'S' 
//                 || game->data->maps->map[i][j]  == 'E' || game->data->maps->map[i][j]  == 'W' )
//                 square(game->img, x, y, 0xffffffff);
//             if (game->data->maps->map[i][j]  == 'N' || game->data->maps->map[i][j] == 'S' 
//                 || game->data->maps->map[i][j]  == 'E' || game->data->maps->map[i][j]  == 'W')
//             {
//                 game->player_x = x + 25;
//                 game->player_y = y + 25;
//                 check_dir(game);
//                 printf("%f\n", game->dir_angle);
//                 // break ;
//             }
//             x += TILESIZE;
//             j++;
//         }
//         y += TILESIZE;
//         x = 0;
//         i++;
//     }   
   
//     sphere(game, 0xed2100ff);
// }

///hadi mezyana
void init_game_data(t_game *game)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    
    game->ray = malloc(sizeof(ray_cast) * WIDTH);
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    while (game->data->maps->map[i])
    {
        j = 0;
        while (game->data->maps->map[i][j] != '\0')
        {
            if (game->data->maps->map[i][j] == '1')
                square(game->img, x, y);
            else if (game->data->maps->map[i][j] == '0' || game->data->maps->map[i][j] == 'N' || game->data->maps->map[i][j] == 'S' 
                || game->data->maps->map[i][j] == 'E' || game->data->maps->map[i][j] == 'W' )
                square1(game->img, x, y);
            if (game->data->maps->map[i][j] == 'N' || game->data->maps->map[i][j] == 'S' 
                || game->data->maps->map[i][j] == 'E' || game->data->maps->map[i][j] == 'W')
            {
                game->player_x = x + 25;
                game->player_y = y + 25;
                check_dir(game);
                // break ;
            }
            x += TILESIZE;
            j++;
        }
        y += TILESIZE;
        x = 0;
        i++;
    }
    sphere(game, 0xed2100ff);
}