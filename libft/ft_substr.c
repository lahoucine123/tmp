/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:11:56 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/23 16:39:05 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	counter;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	if (len > (str_len - start))
		len = str_len - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	counter = 0;
	while (counter < len)
	{
		str[counter] = s[start + counter];
		counter++;
	}
	str[counter] = 0;
	return (str);
}
