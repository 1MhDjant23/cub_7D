/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:37:20 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 18:00:48 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*extract_element(char *line, int j, char *src, t_cub *data)
{
	int		i;
	int		x;
	int		count;

	count = 0;
	i = 0;
	x = 0;
	if (!line)
		return (NULL);
	x += skip_spaces(src);
	if ((src[x] == 'C' || src[x] == 'F') && argcolor(data, &src[x + 1], j, x))
		return (argcolor(data, &src[x + 1], j, x));
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
			err_or(data, " Bad info encountered.", ft_itoa(j), 0);
	}
	return (free(src), ft_substr(line, 0, until_new_line(line)));
}

bool	sub_condition(char *line, int i)
{
	if (line[i] && ((line[i] == 'N' && line[i + 1] == 'O') \
		|| (line[i] == 'S' && line[i + 1] == 'O') \
		|| (line[i] == 'W' && line[i + 1] == 'E') \
		|| (line[i] == 'E' && line[i + 1] == 'A')))
		return (true);
	return (false);
}

bool	check_line_element(t_help *help, char *line, t_cub *data)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (false);
	if (line[i] && line[i] == ' ')
		i += skip_spaces(&line[i]);
	if (line[i] && line[i] == '\n')
		return (false);
	if (sub_condition(line, i))
	{
		if (ft_strncmp(&line[i], "NO ", 3) && ft_strncmp(&line[i], "SO ", 3) \
			&& ft_strncmp(&line[i], "EA ", 3) && ft_strncmp(&line[i], "WE ", 3))
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
			i += skip_spaces(&line[i]);
			return (&line[i]);
		}
		i++;
	}
	return (NULL);
}

bool	without_info(char *line)
{
	int	i;

	i = 0;
	i += skip_spaces(line);
	if (line[i] && (line[i] == 'N' || line[i] == 'S' \
		|| line[i] == 'E' || line[i] == 'W'))
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
