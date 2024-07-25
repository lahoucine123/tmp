/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:45 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 15:06:26 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size > 0)
	{
		while (dst[counter])
			counter++;
		while (counter < size -1 && *src)
		{
			dst[counter] = *src;
			counter++;
			src++;
		}
		dst[counter] = 0;
	}
	if (counter > size)
		counter = size;
	while (*src)
	{
		counter++;
		src++;
	}
	return (counter);
}
