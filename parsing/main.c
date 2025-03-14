/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:28:54 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/12 10:53:21 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	get_row(void)
// {
	
// }

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

int	main(int ac, char **av)
{
	(void)ac;
	t_cub	data;
	t_game game;

	init_data(&data, NULL, NULL, DATA);
	if (!check_valid_extension(av[1]))
		return (1);
	data.file = av[1];
	first_step_to_map(&data);
	reset_map_as_needed(&data);
	int	i = 0;
	while (data.maps->map[i])
		printf("$%s$\n", data.maps->map[i++]);
	// printf("%lu\n", strlen("     1  1111111111111111111111111111111"));
	// printf("%s\n", data.maps->CE_color);
	// printf("[%d]\n", data.maps->column);
	// printf("[%d]\n", data.maps->rwo);
	// printf("%s\n", data.maps->FL_color);
	// printf("%s\n", data.maps->N_texture);
	// printf("%s\n", data.maps->W_texture);
	// printf("%s\n", data.maps->S_texture);
	// printf("%s\n", data.maps->E_texture);
	// printf("%d\n", data.maps->pl_xx);
	// printf("%d\n", data.maps->pl_yy);
	// print_position(data.maps->start_position);

	
	// printf("%s\n", data.maps->E_texture);
	printf("\n\n<<<<<<<<<<<< Map is good >>>>>>>>>>>\n\n");
	game.data = &data;
	game.mlx =  mlx_init(WIDTH, HEIGHT, "cub", 0);
    init_game_data(&game);
    mlx_key_hook(game.mlx, key_hook, &game);
    mlx_image_to_window(game.mlx, game.img, 0, 0);    
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
	return (0);
}
