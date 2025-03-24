/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_V1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:41:21 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/24 14:44:29 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*join_obj_with_path(t_cub *data, char *s1, char *s2)
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
		exit(free_struct(data));
	i = skip_spaces(s2);
	count = 0;
	while (s2[i] && s2[i] != ' ')
		new[count++] = s2[i++];
	i = 0;
	while (i < (int)ft_strlen(s1))
		new[count++] = s1[i++];
	new[count] = '\0';
	free(s2);
	return (new);
}

void	sub_check(t_cub *data, char **line, int *i)
{
	char	*new;
	char	*path;

	new = NULL;
	if (check_line_element(data->help, *line, data) == true \
		&& without_info(*line) == false)
		err_or(data, "Invalid character(or line) between element", ft_itoa(*i), 0);
	else if (just_empty_line(*line) == false)
	{
		path = just_path(*line);
		new = extract_element(path, *i, *line, data);
		*line = join_obj_with_path(data, new, *line);
		if (path)
			free(path);
		if (ft_strlen(*line) <= 2 || !new)
			err_or(data, "element without specific informations", ft_itoa(*i), 0);
		free(new);
		new = NULL;
	}
	(*i)++;
}

void	first_check_of_elem(t_cub *data)
{
	t_filling	*mp;
	int			i;

	i = 1;
	init_data_2(data->help, NULL, HELP);
	mp = data->filling;
	while (mp)
	{
		if (data->count_elem > 6)
		{
			simple_err(data, "too many elements\n");
		}
		if (find_all_elem(data->help) == true)
			break ;
		sub_check(data, &mp->line, &i);
		mp = mp->next;
	}

	while (mp && just_empty_line(mp->line) == true)
	{
		i++;
		mp = mp->next;
	}
	if (!mp)
		free_struct(data);
	data->begin_map = i;
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
			// printf("*%s\n", mp->line);
			path_if_exist(data, mp->line);
			color_valid(data, data->help, mp->line);
			
		}
		mp = mp->next;
		(help->i)++;
	}
}
