/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:11:05 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 18:08:03 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	index;
	char	*str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	index = 0;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	while (*s)
	{
		str[index] = f(index, *s);
		index++;
		s++;
	}
	str[index] = 0;
	return (str);
}
