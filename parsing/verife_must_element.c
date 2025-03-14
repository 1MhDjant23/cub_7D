/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verife_must_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:04:20 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/13 18:16:35 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	convert_floor_celing_color(char *text_color)
{
	(void)text_color;
	// printf("%s\n", text_color);
	// char	**rgba;

	// rgba = ft_split(text_color, ',');
	// if (!rgba)
	// 	exit(write(2, "malloc\n", 7));
	// printf("#%s\t%s\t%s#\n", rgba[0], rgba[1], rgba[2]);
	
	return 0;
}

void	expand_texture(t_cub *data, char *info)
{
	if (!info)
		return ;
	if (info[0] && info[0] == 'N')
		data->maps->N_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'S')
		data->maps->S_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'W')
		data->maps->W_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'E')
		data->maps->E_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'C')
		data->maps->CE_color = convert_floor_celing_color(&info[1]);
	if (info[0] && info[0] == 'F')
		data->maps->FL_color = convert_floor_celing_color(&info[1]);
}


// char	*str_for_check(t_stat stat)
// {
// 	char	*str;

// 	str = NULL;
// 	if (stat == NORTH)
// 		str = "NO ";
// 	else if (stat == SOUTH)
// 		str = "SO ";
// 	else if (stat == WEST)
// 		str = "WE ";
// 	else if (stat == EAST)
// 		str = "EA ";
// 	else if (stat == FLOOR)
// 		str = "F ";
// 	else if (stat == CEILING)
// 		str = "C ";
// 	return (str);
// }

// void	extr_val_of_elem(char *elemnt, t_help *help)
// {
// 	int	i;
// 	int	count;
// 	int	keep;

// 	count = 0;
// 	i = 0;
// 	i += skip_spaces(elemnt);
// 	keep = i;	
// 	while (elemnt[i] && elemnt[i] != '\n')
// 	{
// 		i++;
// 		count++;	
// 	}
// 	if (elemnt[i - 1] == ' ')
// 	{
// 		i--;
// 		while (elemnt[i] && elemnt[i] == ' ')
// 		{
// 			i--;
// 			count--;
// 		}
// 	}
// 	if (count < 0)
// 		return ;
// 	help->tmp = malloc(sizeof(char) * count + 1);
// 	if (!help->tmp)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (elemnt[keep] && elemnt[keep] != '\n' && i < count)
// 		help->tmp[i++] = elemnt[keep++];
// 	help->tmp[i] = '\0';
// }

// void	check_texture_color(t_cub *data, t_stat stat, int index)
// {
// 	char	*st;

// 	st = str_str(data->line_m, str_for_check(stat), data->help);
// 	if (st == NULL)
// 	{
// 		elem_not_found(str_for_check(stat));
// 		free_map_ele(data->maps);
// 		free_all_data(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (index == 0)
// 		data->maps->N_texture = ft_strdup(data->help->tmp);
// 	else if (index == 1)
// 		data->maps->S_texture = ft_strdup(data->help->tmp);
// 	else if (index == 2)
// 		data->maps->W_texture = ft_strdup(data->help->tmp);
// 	else if (index == 3)
// 		data->maps->E_texture = ft_strdup(data->help->tmp);
// 	else if (index == 4)
// 		data->maps->FL_color = ft_strdup(data->help->tmp);
// 	else if (index == 5)
// 		data->maps->CE_color = ft_strdup(data->help->tmp);
// }

// void    check_necessary_elem(t_cub *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 6)
// 	{
// 		init_data(NULL, data->help, NULL, HELP);	
// 		check_texture_color(data, choise_stat(i), i);
// 		if (data->help->tmp == NULL)
// 		{
// 			cannot_find(str_for_check(choise_stat(i)));
// 			free_map_ele(data->maps);
// 			free_all_data(data);
// 			exit(EXIT_FAILURE);
// 		}
// 		free(data->help->tmp);
// 		i++;
// 	}
// 	// ft_strtrim()
// 	printf("NORTH is [%s]\n", data->maps->N_texture);
// 	printf("SOUTH is [%s]\n", data->maps->S_texture);
// 	printf("WEST is [%s]\n", data->maps->W_texture);
// 	printf("EAST is [%s]\n", data->maps->E_texture);
// 	printf("FLOOR is [%s]\n", data->maps->FL_color);
// 	printf("CEILING is [%s]\n", data->maps->CE_color);
// }
