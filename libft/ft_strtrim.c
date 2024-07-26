/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:11:46 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/25 00:25:16 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trim_str_len(char const *s1, char const *set)
{
	size_t	len;

	len = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (*s1)
	{
		len++;
		s1++;
	}
	s1--;
	while (*s1 && ft_strchr(set, *s1))
	{
		len--;
		s1--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = trim_str_len(s1, set);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	str = ft_substr(s1, 0, len);
	if (!str)
		return (NULL);
	return (str);
}
