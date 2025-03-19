/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:28:54 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/18 14:16:46 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_position(t_stat position)
{
	if (position == WEST)
		printf("WEST\n");
	if (position == EAST)
		printf("EAST\n");
	if (position == NORTH)
		printf("NORTH\n");
	if (position == SOUTH)
		printf("SOUTH\n");
}

char	*join_with_spaces(char *str, int size)
{
	char	*s_concat;
	int	i;
	int	j;

	i = 0;
	j = 0;
	s_concat = malloc((ft_strlen(str) + size + 1 ) * sizeof(char));
	if (s_concat == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		s_concat[i] = str[i];
		i++;
	}
	while (j < size - 1)
	{
		s_concat[i++] = ' ';
		j++;
	}
	s_concat[i] = '\0';
	free(str);
	str = NULL;
	return (s_concat);
}

void	reset_map_as_needed(t_cub *data)
{
	size_t	i;

	i = 0;
	while (data->maps->map[i])
	{
		if (ft_strlen(data->maps->map[i]) > (size_t)data->maps->rwo )
		{
			data->maps->map[i] = ft_substr(data->maps->map[i], 0, data->maps->rwo );
		}
		else if (ft_strlen(data->maps->map[i]) < (size_t)data->maps->rwo + 1)
			data->maps->map[i] = join_with_spaces(data->maps->map[i], (data->maps->rwo + 1) - ft_strlen(data->maps->map[i]));
		i++;
	}
		
}

// void	hook_handl(void *param)
// {
// 	t_game *game;
//     game = (t_game *)param;
// 	int	find = 0;
// 	int right = 0;
// 	double	px, py;
// 	px = game->player_x;
// 	py = game->player_y;

// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_S))
// 	{
// 		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
// 		{
// 			px -= SPEED * cos(game->dir_angle);
// 			py -= SPEED * sin(game->dir_angle);
			
// 		}
// 		else
// 		{
// 			px += SPEED * cos(game->dir_angle);
// 			py += SPEED * sin(game->dir_angle);
			
// 		}
	
// 		if (check_for_walls(game, px, py) == -1)
//             find = -1;
// 		if ((game->data->maps->map[(int)px / TILESIZE][(int)py / TILESIZE] != '1') && find != -1) 
// 		{
// 			game->player_x = px;
// 			game->player_y = py;                   
// 			mlx_delete_image(game->mlx, game->img);
// 			render_view(game);
// 		}
// 	}
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_D))
// 	{
// 		if (mlx_is_key_down(game->mlx, MLX_KEY_A))
// 			right = -1;
// 		else
// 			right = 1;
// 		px += right * SPEED * cos(game->dir_angle - M_PI_2);
// 		px += right * SPEED * sin(game->dir_angle - M_PI_2);
// 		if (check_for_walls(game, px, py) == -1)
//             find = -1;
// 		if ((game->data->maps->map[(int)px / TILESIZE][(int)py / TILESIZE] != '1') && find != -1) 
// 		{
// 			game->player_x = px;
// 			game->player_y = py;                   
// 			mlx_delete_image(game->mlx, game->img);
// 			render_view(game);
// 		}
// 	}
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 	{
// 		game->dir_angle += 0.1;
//         game->dir_angle = normalize_ray_angle(game->dir_angle);
// 		mlx_delete_image(game->mlx, game->img);
//         render_view(game);
// 	}
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 	{
// 		game->dir_angle -= 0.1;
//         game->dir_angle = normalize_ray_angle(game->dir_angle);
// 		mlx_delete_image(game->mlx, game->img);
//         render_view(game);
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
//     {
//         exit(0);
//     }
// 	// if (check_for_walls(game, px, py) == -1)
//     //         find = -1;
// 	// if ((game->data->maps->map[(int)px / TILESIZE][(int)py / TILESIZE] != '1') && find != -1) 
// 	// {
// 	// 	game->player_x = px;
// 	// 	game->player_y = py;                   
// 	// 	mlx_delete_image(game->mlx, game->img);
// 	// 	render_view(game);
// 	// }
	
// 	//raycasting here 
	
// }

void	leaks()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	(void)ac;
	t_cub	data;
	t_game game;
	t_pixel pixels;

	// atexit(leaks);
	init_data(&data);
	if (!check_valid_extension(av[1]))
		return (1);
	data.file = av[1];
	first_step_to_map(&data);
	reset_map_as_needed(&data);
	// free(data.maps);
	// printf("%s\n", data.maps->E_texture);
	// printf("%s\n", data.maps->W_texture);
	// printf("%s\n", data.maps->N_texture);
	// printf("%s\n", data.maps->S_texture);
    // pixels = malloc(sizeof(t_pixel));
    // if (!pixels)
    //     exit(EXIT_FAILURE);
	// printf("GOOOOOOOOOOOD\n");
    game.pixels = &pixels;

	game.data = &data;
	game.mlx =  mlx_init(WIDTH, HEIGHT, "cub", 0);
    init_game_data(&game);
    // mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, &key_hook, &game);
    mlx_image_to_window(game.mlx, game.img, 0, 0);    
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
	return (0);
}
