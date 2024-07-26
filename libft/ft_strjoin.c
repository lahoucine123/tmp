/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:39 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 17:32:19 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	index;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) +1;
	index = 0;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	while (*s1)
	{
		str[index] = *s1;
		index++;
		s1++;
	}
	while (*s2)
	{
		str[index] = *s2;
		index++;
		s2++;
	}
	str[index] = 0;
	return (str);
}
