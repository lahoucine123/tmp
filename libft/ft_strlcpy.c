/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:52 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 14:54:11 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;

	length = 0;
	if (size)
	{
		while (src[length] && length < size -1)
		{
			dst[length] = src[length];
			length++;
		}
		dst[length] = 0;
	}
	while (src[length])
		length++;
	return (length);
}
