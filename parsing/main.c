/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:28:54 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 17:29:38 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	char	*tmp;

	i = 0;
	while (data->maps->map[i])
	{
		if (ft_strlen(data->maps->map[i]) > (size_t)data->maps->rwo )
		{
			tmp = data->maps->map[i];
			data->maps->map[i] = ft_substr(data->maps->map[i], 0, data->maps->rwo );
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strlen(data->maps->map[i]) < (size_t)data->maps->rwo + 1)
			data->maps->map[i] = join_with_spaces(data->maps->map[i]\
				,(data->maps->rwo + 1) - ft_strlen(data->maps->map[i]));
		i++;
	}
}


void	leaks()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	(void)ac;
	t_cub	data;
	t_map	maps;
	// t_game game;
	// t_pixel pixels;

	atexit(leaks);
	init_data(&data);
	if (!check_valid_extension(av[1]))
		return (1);
	data.file = av[1];
	data.maps = &maps;
	first_step_to_map(&data);
	reset_map_as_needed(&data);
// printf("$$$$$$$$$$$$$$$$$$$$$\n");
	// while (data.filling)
	// {
	// 	printf("**%s\n", data.filling->line);
	// 	data.filling = data.filling->next;	
	// }
	
	free_map_ele(data.maps);
	// free_struct(&data);
	// free(data.maps->CE_color);
	// free(data.maps->E_texture);
	// // free(data.maps->FL_color);
	// free(data.maps->S_texture);
	// free(data.maps->W_texture);
	// free(data.maps->N_texture);
	// free(data.maps);
	// printf("%s\n", data.maps->E_texture);
	// printf("%s\n", data.maps->W_texture);
	// printf("%s\n", data.maps->N_texture);
	// printf("%s\n", data.maps->S_texture);
    // pixels = malloc(sizeof(t_pixel));
    // if (!pixels)
    //     exit(EXIT_FAILURE);
	printf("\nGOOOOOOOOOOOD\n");
    // game.pixels = &pixels;

	// game.data = &data;
	// game.mlx =  mlx_init(WIDTH, HEIGHT, "cub", 0);
    // init_game_data(&game);
    // // mlx_key_hook(game.mlx, key_hook, &game);
	// mlx_loop_hook(game.mlx, &key_hook, &game);
    // mlx_image_to_window(game.mlx, game.img, 0, 0);    
    // mlx_loop(game.mlx);
    // mlx_terminate(game.mlx);
	return (0);
}
