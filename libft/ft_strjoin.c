/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:56:36 by mait-taj          #+#    #+#             */
/*   Updated: 2025/01/05 12:44:24 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_concat;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return ((char*)s2);
	len = ft_strlen(s1) + ft_strlen(s2);
	s_concat = malloc((len + 1) * sizeof(char));
	if (s_concat == NULL)
		return (NULL);
	while (s1[i])
	{
		s_concat[i] = s1[i];
		i++;
	}
	while (s2[j])
		s_concat[i++] = s2[j++];
	free((char*)s1);
	s_concat[i] = '\0';
	return (s_concat);
}
