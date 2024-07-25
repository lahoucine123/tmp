/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:19 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 16:12:08 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src)
	{
		if (*src == (unsigned char)c)
			return (src);
		src++;
	}
	if (*src == (unsigned char)c)
		return (src);
	return (NULL);
}
