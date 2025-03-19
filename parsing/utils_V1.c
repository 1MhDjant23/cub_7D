/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_V1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:41:21 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/18 13:15:08 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



char	*just_path(char *line, t_help *help)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	(void)help;
	if (line[0] && line[0] == ' ')
		i += skip_spaces(line);
	while (line[i])
	{
		if (line[i] == ' ') 
		{
			i += skip_spaces(&line[i]);      //if encounter a leaks .here one byte...
			return (&line[i]);
		}
			i++;
	}
	return (NULL);
}

char	*join_obj_with_path(char *s1, char *s2)
{
	int		i;
	char	*new;
	int		count;

	i = 0;
	count = 0;
	i += skip_spaces(s2);
	while (s2[i] && s2[i] != ' ')
	{
		count++;
		i++;
	}
	new = malloc(sizeof(char) * count + ft_strlen(s1) + 1);
	if (!new)
		exit(EXIT_FAILURE);
	i = skip_spaces(s2);
	count = 0;
	while (s2[i] && s2[i] != ' ')
		new[count++] = s2[i++];
	i = 0;
	while (i < (int)ft_strlen(s1))
		new[count++] = s1[i++];
	new[count] = '\0';
	return (new);
}

void	exit_here(t_game *data)
{
	(void)data;
	// free_struct(data);
	// free(data->help->tmp);
	// free_map_ele(data->maps);
	// exit(write(2, "too many element in the map\n", 28));
}

void	first_check_of_elem(t_cub *data)
{
	t_filling	*mp;
	char		*new;
	int			i;

	i = 1;
	init_data_2(data->help, NULL, HELP);
	mp = data->filling;
	while (mp)
	{
		if (data->count_elem > 6)
			exit(1);
			// exit_here(data);
		if (find_all_elem(data->help) == true)
			break ;
		if (check_line_element(data->help, mp->line, data) == true \
			&& without_info(mp->line) == false)
			exit(print_errline(ft_itoa(i), "Error\nInvalid character(or line) between element "));
		else if (just_empty_line(mp->line) == false)
		{
			new = extract_element(just_path(mp->line, data->help), i, mp->line, data->help->x);
			mp->line = join_obj_with_path(new, mp->line);
			if (ft_strlen(mp->line) <= 2 || !new)
			{
				print_errline(ft_itoa(i), NULL);
				exit(err("') element without specific informations\n"));
			}
		}
		i++;
		mp = mp->next;
	}
	while (mp && just_empty_line(mp->line) == true)
	{
		i++;
		mp = mp->next;
	}
	if (!mp)
		data->filling = NULL;
	data->begin_map = i;
}

bool	without_info(char *line)
{
	int	i;

	i = 0;
	i += skip_spaces(line);
	if (line[i] && (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
	{
		if (line[i + 2] == '\n')
			return (true);
	}
	else if (line[i] && (line[i] == 'F' || line[i] == 'C'))
	{
		if (line[i + 1] == '\n')
			return (true);
	}
	return (false);
}

bool	check_line_element(t_help *help, char *line, t_cub *data)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (false);
	if (line[i] && line[i] == ' ')
		i+= skip_spaces(&line[i]);
	if (line[i] && line[i] == '\n')
		return (false);
	if (line[i] && ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A')))
	{
		if (ft_strncmp(&line[i], "NO ", 3) && ft_strncmp(&line[i], "SO ", 3) && ft_strncmp(&line[i], "EA ", 3)
				&& ft_strncmp(&line[i], "WE ", 3))
			return (true);
	}
	else if (line[i] && ((line[i] == 'F') || (line[i] == 'C')))
	{
		if (ft_strncmp(&line[i], "F ", 2) && ft_strncmp(&line[i], "C ", 2))
			return (true);
	}
	else
		return (true);
	if (line[i])
		set_bool(help, line[i], data);
	return (false);
}

char	*extract_element(char *line, int index, char *src, int x)
{
	int		i;
	int		count;
	char	*new;

	count = 0;
	i = 0;
	x = 0;
	if (!line)
		return (NULL);
	x += skip_spaces(src);
	if ((src[x] == 'C' || src[x] == 'F') && valid_arg_color(&src[x + 1], index, x))
		return (valid_arg_color(&src[x + 1], index, x));
	i += skip_spaces(line);
	while (line[i] && line[i] != '\n' && line[i] != ' ')
	{
		count++;
		i++;
	}
	if (line[i] == ' ')
	{
		i += skip_spaces(&line[i]);
		if (line[i] != '\0' && line[i] != '\n')
		{
			write(2, "Error\nBad info encountered in line: `", 37);
			write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
			write(2, "'\n", 2);
			exit(1);
		}
	}
	new = malloc(sizeof(char) * count + 1);
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		new[count++] = line[i++];
	new[count] = '\0';
	return (new);
}

bool	just_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	if (line[i] == '\n')
		return (true);
	if (line[i] == ' ')
		i += skip_spaces(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}

void	all_element_is_good(t_cub *data)
{
	t_filling	*mp;
	t_help		*help;

	help = data->help;
	mp = data->filling;
	init_data_2(data->help, NULL, HELP);
	while (help->i < data->begin_map - 1)
	{
		if (just_empty_line(mp->line) == false)
		{
			path_if_exist(data, mp->line);
			color_valid(data->help, mp->line);
		}
		mp = mp->next;
		(help->i)++;
	}
}





