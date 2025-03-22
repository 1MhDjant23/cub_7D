/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:39:02 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 18:00:36 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_filling	*create_node(t_cub *data, char *content)
{
	t_filling	*node;

	node = malloc(sizeof(t_filling));
	if (!node)
	{
		if (content)
			free(content);
		write(2, "Error\nThe allocation is failing.\n", 33);
		exit(free_struct(data));
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

void	extension_of_textures(t_cub *data, char *path)
{
	char	*tmp;

	if (!path)
		return ;
	tmp = ft_strrchr(path, '.');
	if (!tmp)
		simple_err(data, "path of textures must be a type of `.png`\n");
	if (ft_compare(tmp, ".png") == 0)
		return ;
	simple_err(data, "path of textures must be a type of `.png`\n");
}

void	path_if_exist(t_cub *data, char *line)
{
	char	*path;

	path = NULL;
	// printf("%s\n", line);
	if (line[0] == 'E' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W')
		path = &line[2];
	else
		return ;
	// printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	extension_of_textures(data, path);
	data->help->x = open(path, O_RDONLY);
	if (data->help->x == -1)
		err_or(data, " enter a valid texture!.", ft_itoa(data->help->i), 0);
	close(data->help->x);
}

int	list_size(t_filling *mp)
{
	int	size;

	size = 0;
	while (mp)
	{
		size++;
		mp = mp->next;
	}
	return (size);
}
