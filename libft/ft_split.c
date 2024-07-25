/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:10 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/23 17:56:07 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	array_size(char const *s, char c)
{
	size_t	len;

	len = 1;
	while (*s)
	{
		if (*s != c)
		{
			len++;
			while (*s && *s != c)
				s++;
		}
		if (*s)
			s++;
	}
	return (len);
}

static void	free_array(char **array)
{
	size_t	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static char	**fill_array(char **array, char const *s, char c)
{
	size_t	index;
	char	*start;

	index = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			array[index] = ft_substr(start, 0, s - start);
			if (!array[index])
			{
				free_array(array);
				return (NULL);
			}
			index++;
		}
		if (*s)
			s++;
	}
	array[index] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	array_len;

	if (!s)
		return (NULL);
	array_len = array_size(s, c);
	array = (char **)malloc(array_len * sizeof(char *));
	if (!array)
		return (NULL);
	array = fill_array(array, s, c);
	return (array);
}
