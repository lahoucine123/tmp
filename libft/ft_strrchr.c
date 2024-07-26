/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:11:27 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 15:16:34 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*found_addr;

	found_addr = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			found_addr = (char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		found_addr = (char *)s;
	return (found_addr);
}
