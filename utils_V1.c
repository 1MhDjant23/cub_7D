/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_V1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:41:21 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/01 11:28:55 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_filling	*create_node(char *content)
{
	t_filling	*node;

	node = malloc(sizeof(t_filling));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->line = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	add_node(t_filling **head, t_filling *new)
{
	t_filling	*temp;

	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;		
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
void	first_check_of_elem(t_cub *data)
{
	t_filling	*mp;
	char		*new;
	int			i;

	i = 1;
	init_data(NULL, data->help, NULL, HELP);
	mp = data->filling;
	while (mp)
	{
		if (find_all_elem(data->help) == true)
			break ;
		if (check_line_element(data->help, mp->line) == true && without_info(mp->line) == false)
		{
			write(2, "Error\nInvalid character(or line) between element (line: `", 57);
			write(2, ft_itoa(i), ft_strlen(ft_itoa(i)));
			write(2, "')\n", 3);
			exit(1);
		}
		else if (just_empty_line(mp->line) == false)
		{
			new = extract_element(just_path(mp->line, data->help), i, mp->line, data->help->x);
			mp->line = join_obj_with_path(new, mp->line);
			if (ft_strlen(mp->line) <= 2 || !new)
			{
				write(2, "Error\n(line: `", 14);
				write(2, ft_itoa(i), ft_strlen(ft_itoa(i)));
				write(2, "') element without specific informations\n", 41);
				exit(1);
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

bool	check_line_element(t_help *help, char *line)
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
		set_bool(help, line[i]);
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
	if (line[i] == '\n')
		return (true);
	return (false);
}

void	all_element_is_good(t_cub *data)
{
	t_filling	*mp;
	t_help		*help;

	help = data->help;
	mp = data->filling;
	init_data(NULL, data->help, NULL, HELP);
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

void	is_rgb(char *line, t_help *help)
{
	char	**spl;
	int		i;
	int		res;

	i = 0;	
	spl = ft_split(line, ',');
	if (!spl)
		exit(1);
	while (spl[i])
	{
		res = ft_atoi(spl[i++]);
		if (res > 255 || res < 0)
		{
			write(2, "Error\n(line: `", 14);
			write(2, ft_itoa(help->i + 1), ft_strlen(ft_itoa(help->i + 1)));
			write(2, "'): R,G,B colors must be in range [0,255]\n", 42);
			exit(1);
		}
	}
	free_d_arr(spl);
}

void	argu_ment(char *line, char **splt, int index)
{
	int	i;
(void)splt;
	i = 0;
	i += skip_spaces(line);

	if (line[i] == '\0' || line[i] == '\n')
	{
		write(2, "Error\n(line: `", 14);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		exit(write(2, "');Set valid R,G,B color\n", 25));
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] && line[i] == ' ')
	{
		i += skip_spaces(&line[i]);
		if (line[i] && line[i] != '\n')
		{
			write(2, "Error\n(line: `", 14);
			write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
			exit(write(2, "');space between digit encountered\n", 35));
		}
	}
}

char	*valid_arg_color(char *line, int index, int i)
{
	int		ver;
	char	**spl;

	ver = 0;
	i = 0;
	i += skip_spaces(line);
	if (line[i] == ',')
		exit(write(2, "Error\nSyntax error; R,G,B color\n", 32));
	while (line[i])
	{
		if (( line[i] == '+' && ft_isdigit(line[i + 1])) || (line[i] != ' ' && line[i] != ',' && line[i] != '\n' && !ft_isdigit(line[i])))
			exit(write(2, "Error\nR,G,B color must contain only digit\n", 42));
		if (line[i] == ',' && line[i + 1] == ',')
			break ;
		if (line[i++] == ',')
			ver++;
	}
	if (ver != 2)
	{
		write(2, "Error\nToo many comma `,' in line (", 34);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		exit(write(2, ")!.\n", 4));
	}
	spl = ft_split(line, ','); // hereeeee e e e e e e e e ee  e e e e e e e 
	i = 0;
	while (spl[i])
		argu_ment(spl[i++], spl, index);
	free_d_arr(spl);
	return (&line[1]);
}


void	color_valid(t_help *help , char *line)
{
	int	i;

	i = 1;
	
	if (line[0] && (line[0] == 'C' || line[0] == 'F'))
	{
		i += skip_spaces(&line[i]);
		is_rgb(&line[1], help);
	}
}

void	extensionOfTextures(char *path)
{
	char	*tmp;
	if (!path)
		return ;
	tmp = ft_strrchr(path, '.');
	if (!tmp)
		exit(write(2, "Error\npath of textures must be a type of `.PNG`\n", 48));
	if (ft_compare(tmp, ".PNG") == 0)
		return ;
	exit(write(2, "Error\npath of textures must be a type of `.PNG`\n", 48));
}

void	path_if_exist(t_cub *data, char *line)
{
	char	*path;

	path = NULL;
	if (line[0] == 'E' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W')
		path = &line[2];
	else
		return ;
	extensionOfTextures(path);
	data->help->x = open(path, O_RDONLY);
	if (data->help->x == -1)
	{
		write(2, "Error\n(line `", 13);
		write(2 , ft_itoa(data->help->i + 1), ft_strlen(ft_itoa(data->help->i)));
		write(2, "') enter a valid texture!.\n", 27);
		exit(1);
	}
	close(data->help->x);
}
