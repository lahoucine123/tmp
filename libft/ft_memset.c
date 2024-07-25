/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:09:32 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 14:03:57 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	value;

	count = 0;
	value = (unsigned char)c;
	while (n > count)
	{
		*(unsigned char *)(s + count) = value;
		count++;
	}
	return (s);
}
