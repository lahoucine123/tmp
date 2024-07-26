/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:10:25 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 17:16:28 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	counter;
	char	*cpy;

	len = ft_strlen(s) +1;
	cpy = (char *) malloc(len * sizeof(char));
	if (!cpy)
		return (NULL);
	counter = 0;
	while (s[counter])
	{
		cpy[counter] = s[counter];
		counter++;
	}
	cpy[counter] = 0;
	return (cpy);
}
