/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:09:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 15:53:36 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	found;

	src = (unsigned char *)s;
	found = (unsigned char)c;
	while (n)
	{
		if (*src == found)
			return (src);
		src++;
		n--;
	}
	return (NULL);
}
